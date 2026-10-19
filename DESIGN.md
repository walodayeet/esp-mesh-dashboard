---
name: ESP32 Mesh Telemetry Dashboard
colors:
  primary: "#ffb454"
  background: "#131517"
  surface-1: "#1a1d20"
  surface-2: "#22252870"
  line: "#2e3237"
  line-strong: "#4a4f55"
  text: "#e6e4dc"
  text-dim: "#a8a69b"
  text-faint: "#8a897f"
  live: "#6fbf73"
  warning: "#ffb454"
  stale: "#ee5a5f"
  series-temp: "#ffb454"
  series-humidity: "#a8a69b"
typography:
  display:
    fontFamily: '"Cascadia Mono", ui-monospace, SFMono-Regular, Menlo, monospace'
    fontSize: 1.25rem
    fontWeight: 600
    lineHeight: 1.6rem
    letterSpacing: 0.04em
  heading:
    fontFamily: '"Cascadia Mono", ui-monospace, SFMono-Regular, Menlo, monospace'
    fontSize: 0.625rem
    fontWeight: 600
    lineHeight: 1rem
    letterSpacing: 0.18em
  metric-primary:
    fontFamily: '"Cascadia Mono", ui-monospace, SFMono-Regular, Menlo, monospace'
    fontSize: 3.5rem
    fontWeight: 300
    lineHeight: 3.7rem
  metric:
    fontFamily: '"Cascadia Mono", ui-monospace, SFMono-Regular, Menlo, monospace'
    fontSize: 1.375rem
    fontWeight: 500
    lineHeight: 1.65rem
  body:
    fontFamily: '"Source Sans 3", system-ui, "Segoe UI", Roboto, sans-serif'
    fontSize: 0.8125rem
    fontWeight: 400
    lineHeight: 1.35rem
  caption:
    fontFamily: '"Cascadia Mono", ui-monospace, SFMono-Regular, Menlo, monospace'
    fontSize: 0.6875rem
    fontWeight: 400
    lineHeight: 0.95rem
    letterSpacing: 0.08em
rounded:
  all: 0px
spacing:
  base-unit: 8px
  space-xs: 4px
  space-sm: 8px
  space-md: 16px
  space-lg: 24px
---

## Overview

A 24/7 operator surface for an ESP32 environmental sensor mesh (ESP-NOW multi-hop),
styled as a **field instrument, not an admin panel**: flat graphite, hairline rules
instead of card boxes, square corners everywhere, monospaced data with tabular figures,
one amber signature accent, and state color reserved strictly for meaning
(green live / amber degraded / red silent). Type and fonts are bundled locally
(Cascadia Mono, Source Sans 3 — both OFL); no CDN, no webfont fetch, no build step.

The interface answers five questions at a glance, in this order:

1. Is the mesh healthy — how many stations report now versus silent.
2. What is the selected station measuring right now (dominant reading, with unit).
3. How fresh is each value.
4. What is the trend.
5. What needs attention (stale/silent stations, gateway state).

Non-goals: marketing surfaces, decorative gradients, glassmorphism, feature panels
the backend cannot feed.

## Colors

Flat, warm-graphite regime. Color never decorates — it encodes operational state
and one signature accent.

| Role | Token | Value |
| --- | --- | --- |
| Base canvas | `background` | `#131517` |
| Raised block (chart frame, log rows) | `surface-1` | `#1a1d20` |
| Hover wash (translucent) | `surface-2` | `#22252870` |
| Hairline rule | `line` | `#2e3237` |
| Emphasis rule / focus | `line-strong` | `#4a4f55` |
| Text primary | `text` | `#e6e4dc` |
| Text secondary | `text-dim` | `#a8a69b` |
| Text faint (ages, stamps, labels) | `text-faint` | `#8a897f` |
| Nominal / live | `live` | `#6fbf73` |
| Signature accent + degraded | `warning` / `primary` | `#ffb454` |
| Silent / offline | `stale` | `#ee5a5f` |
| Chart series: temperature / humidity | `series-temp` / `series-humidity` | `#ffb454` / `#a8a69b` |

Reading pairs meet WCAG AA 4.5:1 on both canvases used: text 13.3–14.4:1,
dim 6.9–7.5:1, faint 4.8–5.2:1, live 7.6–8.2:1, warning 9.6–10.4:1,
stale 4.7–5.1:1. The signature accent doubles as the degraded-state color;
the health headline and metric values disambiguate by number and text, never by hue alone.

## Typography

Two bundled faces, both doing instrument work:

- **Cascadia Mono** (variable, OFL): every numeric value, timestamp, unit, tag,
  section header and the health headline. Tabular figures (`font-variant-numeric:
  tabular-nums`) so live values do not shift layout. Headers are uppercase with
  0.14–0.18em tracking at 10px — ruler markings, not titles.
- **Source Sans 3** (variable, OFL): running text only — empty states, banner copy,
  log lines that are sentences.

Scale: display 3.5rem/300 (primary metric), metric 1.375rem/500, headline 1.25rem/600
uppercase, caption 0.6875rem, body 0.8125rem.

## Layout

8-point rhythm, hairline-separated bands, no boxed cards.

- **Desktop >= 1280px**: left rail (station roster, mono, 264px) + main column.
  Main bands top-to-bottom: headline + status tags, health segments bar, gateway banner
  (when active), metric strip (one dominant reading + three secondary cells separated by
  vertical hairlines), chart, event log.
- **Tablet 768-1279px**: rail narrows to 216px; metric strip reflows to a full-width
  dominant reading over a 2-up grid.
- **Mobile < 768px**: single column; rail folds below the main column (headline, tags,
  metrics, chart first; roster strip; log last). No horizontal scroll.

The health headline is always the first readable element.

## Elevation & Depth

None. No shadows, no blur, no glassmorphism, no gradients. Depth = the two flat
surfaces (`background`, `surface-1`) separated by 1px hairlines. Hover is a 12%-alpha
wash of `#222528`. Focus is a 1px amber outline, offset 1px.

## Shapes

Zero border-radius everywhere — inputs, tags, chart frame, banner, bars. Signal-strength
bars are 2px-wide rectangles. The health segments bar is a 4px square-edged strip.
State indicators are bracketed text tags (`LIVE`, `WARNING`, `STALE`), not dot pills.

## Components

- **Health headline**: `1/3 STATIONS REPORTING · 1 DEGRADED · 1 SILENT` — counts in
  `text`, words in mono uppercase; tone tints the count (green/amber/red).
- **Segments bar**: 4px strip under the headline; live/degraded/silent proportions;
  square edges.
- **Status tags**: 1px bordered square chips, mono, uppercase (`STREAM CONNECTED`,
  `GATEWAY OFFLINE`, `LIVE`); border and text take the state color.
- **Metric strip**: dominant reading (3.5rem light mono + unit) left; humidity/signal/
  battery cells right, separated by vertical hairlines; per-cell age line
  (`19:36:36 · 3 s ago`, or `not reporting, last seen …` when stale).
- **Trend chart**: canvas in a 1px `line` frame on `surface-1`; amber temperature line
  (left axis, °C), grey humidity line (right axis, % RH); solid hairline grid; in-frame
  axis labels; timestamp ticks on the bottom rule; gaps where samples are missing.
- **Station roster**: flat rows — station id (mono 600), signal bars + dBm + battery
  line, right-aligned last-seen age colored by state; selected row gets a 2px amber
  left edge; separated by hairlines, no boxes.
- **Event log**: mono lines, newest first; station id bold-left column, timestamp +
  message; dropped/rejected entries in `stale`.
- **Gateway banner**: full-width 1px amber (or stale) bordered strip with `!` prefix,
  mono copy, only when gateway/stream state is degraded.

## Do's and Don'ts

**Do**

- Encode state with text and position so it survives without color.
- Use tabular figures for everything numeric; right-align columns.
- Label every axis with its unit, inside the frame.
- Show staleness for every value; make a silent station visually inert.
- Keep all color decisions in the `:root` of the single stylesheet.

**Don't**

- Don't plot missing samples as zero.
- Don't claim a gateway is up because a websocket opened.
- Don't ship screens the backend cannot feed.
- Don't round corners, add shadows, gradients, glow, glass, or dot-pill chips —
  they are the signature of generated dashboards, not instruments.
- Don't rely on hover-only states on touch.
- Don't animate anything except state changes; respect reduced motion.
