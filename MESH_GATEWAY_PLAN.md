# Signal Strength + Automated Insights Plan

## Context

Add the user-requested signal-strength display and AI/insight feature to the ESP32 mesh dashboard. Scope is limited to these two features; the forwarded feature list is context, not an expanded requirement. Use the existing custom ESP-NOW mesh in `mesh-node`, bridge a gateway to the dashboard host by USB serial, and make insights deterministic statistical summaries—not trained or rain/fire predictions.

## Approach

1. **Add a USB-serial ESP-NOW gateway firmware mode while preserving sensor-node mode.**
   - In `mesh-node/src/main.cpp`, keep the current sensor-node behavior as default. Add a `MESH_GATEWAY` compile-time mode: initialize the same `EspNowMesh`, do not register/sample the LDR or transmit sensor readings, and serialize every accepted mesh receive callback as one newline-terminated JSON frame on USB serial at 115200 baud. Gateway stdout/serial must contain only frames; diagnostic text must not corrupt NDJSON.
   - In `mesh-node/platformio.ini`, add `[env:esp32-gateway]` using the existing board/framework and `-DMESH_GATEWAY`; keep `[env:esp32dev]` unchanged.
   - Extend `MeshMessage` in `mesh-node/include/EspNowMesh.h` with a per-boot `uint64_t bootId`, initialized once from ESP hardware randomness in `EspNowMesh::begin()`, set on locally published packets and preserved when relayed. Include `bootId` in the duplicate-cache key `(origin, bootId, sequence)` in `EspNowMesh::hasSeen()` / `remember()`. Keep the existing packet-size static assertion and compile both firmware environments; all mesh nodes and gateway must be reflashed together because wire layout changes.
   - Emit frame shape: `{"origin":"AA:BB:CC:DD:EE:FF","bootId":"0123456789abcdef","sequence":42,"hops":1,"rssi":-61,"rssiSourceNodeId":"AA:BB:CC:DD:EE:FF","readings":[{"sensorId":"ldr1","channel":"raw","value":1234,"unit":"adc_counts"}]}`. `origin`, `bootId`, `sequence`, and `hops` come from `MeshMessage`; `rssi` and `rssiSourceNodeId` come from `MeshReceiveInfo` (the immediate radio sender). Use JSON `null` when RSSI is `-128`. Embed the `SensorManager::getReadingsJson()` array as `readings`, not as an escaped string.

2. **Bridge gateway NDJSON to the existing FastAPI telemetry pipeline.**
   - Add `pyserial>=3.5,<4.0` to `Dashboard/requirements.txt`; update `Dashboard/.env.example` with `MESH_TRANSPORT=serial` and `MESH_SERIAL_PORT` examples for a Linux device and `COM3`.
   - Use FastAPI lifespan in `Dashboard/main.py` to start/stop a serial reader only for `MESH_TRANSPORT=serial`. Reuse `MeshReceiver.connect_gateway()`, `handle_message()`, and `broadcast_event()`. The reader uses a dedicated worker thread with serial read timeout 1 second; it forwards complete lines to the asyncio loop, closes the port on shutdown, and retries opening a lost port every 2 seconds. A malformed or non-JSON boot line is logged and ignored; it must not terminate the reader or app. Serial disconnect sets gateway status false.
   - Convert each frame to the dashboard envelope: `nodeId=origin`; `timestamp` = host receipt UTC in ISO-8601 `Z` form (not sensor sample time); `sequence` = source sequence; retain `bootId`, `rssi`, `rssiSourceNodeId`, `hops`; map each reading to payload key `<sensorId>.<channel>` and matching `units` key. Skip non-finite/null reading values. Reject a frame with no valid numeric readings or duplicate generated metric keys.
   - Extend `Dashboard/mesh_protocol.py` to validate optional `bootId` as 16 lowercase hex chars, finite optional RSSI (`-128` means unavailable), non-empty optional RSSI source MAC, integer hops 0–255, and string-valued `units` mapping. Keep current required fields and numeric-payload contract.
   - Extend `MeshReceiver.handle_message()` and its REST/history/WS projections to preserve `bootId`, `rssi`, `rssiSourceNodeId`, `hops`, and `units`. Each history sample stores these metadata alongside timestamp, sequence, and payload; each live WebSocket telemetry event includes them. For messages with boot IDs, duplicate/order rejection is scoped to `(nodeId, bootId)` so a reboot may restart sequence at 0. Legacy messages without boot IDs retain current strict sequence behavior. `/nodes` and `/nodes/{id}` expose last-hop RSSI source and hop count without implying it is the originating node's direct link.

3. **Make signal strength and mesh diagnostics visible and truthful.**
   - Reuse the existing station roster signal bars and signal metric in `Dashboard/frontend/app.js`; no parallel widget. Render `LAST-HOP RSSI` only when supplied, display its `rssiSourceNodeId`, and show hop count when available. Missing/null RSSI displays `RSSI UNAVAILABLE`, never a fabricated value. Keep existing bar thresholds; numeric dBm is authoritative.
   - Restore source `sequence` in the selected-station telemetry header as `SEQ <number>` and include it in telemetry log entries. Carry it through initial `/nodes`, history, station selection, and WebSocket updates. Show boot ID only in diagnostic detail/log text, not as a headline metric.

4. **Implement a deterministic insight API over the existing bounded history.**
   - Add pure calculations in new `Dashboard/insights.py`, using ordered per-node history only; no LLM, ML dependencies, external service, model download, or persistence. Analyze finite numeric sensor payload keys independently; use matching `units` when available; exclude RSSI and mesh metadata from sensor insights.
   - Add `GET /nodes/{node_id}/insights` in `Dashboard/main.py`. Unknown node returns 404, matching `/nodes/{node_id}`. Known node response is exactly `{"nodeId":"...","generatedAt":"<UTC ISO-8601 Z>","sampleCount":N,"insights":[...]}`. Empty/insufficient history returns 200 with empty insights and actual sample count.
   - For each metric, produce at most one anomaly and one trend, sorted by metric key, anomaly before trend:
     - Anomaly: compare newest finite value against up to the preceding 100 finite samples; require at least 20 baseline samples. Compute arithmetic mean and population standard deviation. Flag only if absolute deviation is greater than 2 standard deviations; if deviation is zero, flag any unequal current value. Return `{kind:"anomaly",metric,unit,severity:"warning",value,mean,stddev,baselineSamples,message}`. Message says unusually high/low relative to baseline; no causal or predictive claim.
     - Trend: require 20 finite samples; compare mean of the preceding 10 to mean of the latest 10. Direction is rising/falling when delta magnitude exceeds `max(1e-9, 0.01 * max(abs(priorMean), abs(recentMean)))`; otherwise steady. Return `{kind:"trend",metric,unit,direction,delta,comparisonSamples:20,message}`.
   - The analysis window is the existing `HistoryBuffer` retention (currently 1,000 samples/node); never label it daily/weekly. Current firmware only emits an LDR `raw` ADC reading about every 3 seconds, so current insights describe ADC trends, not temperature, rain, or fire.

5. **Show transparent insights for the selected node.**
   - Add an `AUTOMATED INSIGHTS` panel to `Dashboard/frontend/dashboard.html` and style it in `styles.css` using existing tokens. Subtitle is exactly `STATISTICAL RULES · NO PREDICTION MODEL`.
   - In `Dashboard/frontend/app.js`, fetch `/nodes/{id}/insights` on selection and every 30 seconds for the selected node. Clear old-node insight content immediately on selection change. Insert returned message text with `textContent`, not `innerHTML`. For fewer than 20 usable samples show `Collecting baseline: <N>/20 valid samples.`; with no numeric sensor samples show `No numeric sensor history available.`; on failure show `Insights temporarily unavailable.`

## Critical files & anchors

- `mesh-node/include/EspNowMesh.h` — `MeshMessage`, `MeshReceiveInfo`, and `SeenPacket` define wire layout, hop RSSI, and duplicate identity.
- `mesh-node/src/EspNowMesh.cpp` — `begin()`, `publishTo()`, `hasSeen()`, `remember()`, `onReceive()` own packet identity/relay/RSSI metadata.
- `mesh-node/src/main.cpp` — `setup()`, 3-second LDR loop, and `printMessage()`; preserve default node mode while adding gateway mode.
- `Dashboard/receiver.py` and `Dashboard/mesh_protocol.py` — serial stub, strict message normalization, sequence guard, history, REST/WS event projections.
- `Dashboard/frontend/app.js` — `renderRoster()`, `renderMetrics()`, `loadHistory()`, `onTelemetry()`, and `selectStation()` carry RSSI/source/sequence and selected-node insight state.

## Verification

- `cd Dashboard && pytest -q`: existing suite plus gateway-frame conversion, optional metadata propagation through REST/history/WS, malformed-line recovery, same-boot duplicate rejection, new-boot sequence reset, insight algorithm and API tests.
- `cd mesh-node && pio run -e esp32dev && pio run -e esp32-gateway`: both environments compile and packet-size assertion passes.
- PTY end-to-end check: run FastAPI with `MESH_TRANSPORT=serial` and a pseudo-terminal device; send the concrete gateway frame in step 1. Verify `/nodes`, `/nodes/{id}/history`, and an actual `/live` WebSocket all expose identical source sequence/RSSI/source/hops/units; invalid lines do not stop later valid frames.
- Insight behavior: 19 finite values => no insight; 10 values at 100 followed by 10 at 120 => rising trend delta 20; constant 20-sample baseline followed by 500 => anomaly warning. Verify 404 for unknown node and exact response shape.
- Browser scenario on the PTY fixture: after 20 readings, selected node shows API-matching insight text/units; switching nodes clears old text immediately; absent RSSI renders unavailable. Check desktop and mobile widths and browser console.
- Hardware scenario: flash all mesh nodes and the gateway with the shared new layout, connect the gateway by USB serial, and verify actual origin MAC, last-hop source MAC, hops, sequence, RSSI, and LDR readings. If hardware is unavailable, report builds + PTY E2E as verified and physical-radio verification as pending; do not inject synthetic readings into the user's dashboard.

## Assumptions & contingencies

- Scope is only signal strength and deterministic insights. The forwarded agent suggestions for duty-cycle controls, thresholds UI, CSV export, event annotations, weekly summaries, solar state, and topology maps are not included.
- The `mesh-root/` ESP-IDF `esp_mesh` firmware is a separate stack that currently logs packets only. Use `mesh-node/` custom ESP-NOW for both sensor nodes and gateway; do not mix stacks.
- The only inspected sensor implementation is LDR `ldr1.raw` in `adc_counts`, sent about every 3 seconds. Keep insight calculations generic over numeric payload keys, but do not claim temperature/humidity/rain/fire predictions.
- Gateway has no verified clock; timestamp at host receipt and label as received/last seen, not sensor-sampled time.
- USB serial is the selected gateway link at 115200 baud; `MESH_SERIAL_PORT` selects Linux device or Windows COM port. If unavailable, keep the dashboard running, report gateway disconnected, and retry every 2 seconds.
- Adding `bootId` changes the custom ESP-NOW wire layout; all sensor nodes and gateway must be reflashed together. Mixed old/new firmware is incompatible.
