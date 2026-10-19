#include <Arduino.h>
#include "EspNowMesh.h"

#ifdef MESH_GATEWAY

#include <cstdio>
#include <cstring>

EspNowMesh mesh;

void gatewayMessageCallback(const MeshMessage &message,
                            const MeshReceiveInfo &receiveInfo,
                            void *context)
{
  (void)context;
  char origin[18];
  std::snprintf(origin, sizeof(origin), "%02X:%02X:%02X:%02X:%02X:%02X",
                message.origin[0], message.origin[1], message.origin[2],
                message.origin[3], message.origin[4], message.origin[5]);

  char bootId[17];
  std::snprintf(bootId, sizeof(bootId), "%016llx",
                static_cast<unsigned long long>(message.bootId));

  char source[18];
  std::snprintf(source, sizeof(source), "%02X:%02X:%02X:%02X:%02X:%02X",
                receiveInfo.sender[0], receiveInfo.sender[1],
                receiveInfo.sender[2], receiveInfo.sender[3],
                receiveInfo.sender[4], receiveInfo.sender[5]);

  char rssiBuf[16];
  if (receiveInfo.rssi == static_cast<int8_t>(-128))
  {
    std::snprintf(rssiBuf, sizeof(rssiBuf), "null");
  }
  else
  {
    std::snprintf(rssiBuf, sizeof(rssiBuf), "%d", static_cast<int>(receiveInfo.rssi));
  }

  // Ensure gateway stdout/serial contains only valid NDJSON frames
  if (message.payloadLength > 0 && message.payload[0] == '[')
  {
    Serial.printf("{\"origin\":\"%s\",\"bootId\":\"%s\",\"sequence\":%lu,\"hops\":%u,\"rssi\":%s,\"rssiSourceNodeId\":\"%s\",\"readings\":%.*s}\n",
                  origin, bootId, static_cast<unsigned long>(message.sequence),
                  message.hops, rssiBuf, source,
                  static_cast<int>(message.payloadLength),
                  reinterpret_cast<const char *>(message.payload));
  }
  else
  {
    Serial.printf("{\"origin\":\"%s\",\"bootId\":\"%s\",\"sequence\":%lu,\"hops\":%u,\"rssi\":%s,\"rssiSourceNodeId\":\"%s\",\"readings\":[]}\n",
                  origin, bootId, static_cast<unsigned long>(message.sequence),
                  message.hops, rssiBuf, source);
  }
}

void setup()
{
  Serial.begin(115200);

  // Give the serial monitor time to connect when using the ESP32-S3 USB port.
  const unsigned long serialStart = millis();
  while (!Serial && millis() - serialStart < 5000)
  {
    delay(10);
  }

  while (!mesh.begin())
  {
    Serial.println("[GATEWAY] mesh.begin failed; retrying in 1s...");
    delay(1000);
  }
  mesh.setMessageHandler(&gatewayMessageCallback);
}

void loop()
{
  mesh.update();
  delay(1);
}

#else

#include "SensorManager.h"
#include "LdrSensor.h"

#include <cstring>

// put function declarations here:
void printMessage(const MeshMessage &message, const MeshReceiveInfo &receiveInfo, void *context);

EspNowMesh mesh;
SensorManager sensorManager;
LdrSensor ldrSensor("ldr1", 34);

unsigned long lastUpdate = 0;
bool meshReady = false;

void setup()
{
  ldrSensor.begin();
  sensorManager.add(ldrSensor);

  Serial.begin(115200);

  // Give the serial monitor time to connect when using the ESP32-S3 USB port.
  const unsigned long serialStart = millis();
  while (!Serial && millis() - serialStart < 5000)
  {
    delay(10);
  }

  Serial.println("ESP-NOW Mesh Example");
  if (!mesh.begin())
  {
    Serial.println("Failed to initialize ESP-NOW Mesh");
    Serial.flush();
    return;
  }
  Serial.println("ESP-NOW Mesh initialized successfully");
  mesh.setMessageHandler(&printMessage);
}

void loop()
{
  mesh.update();

  unsigned long currentTime = millis();
  if (currentTime - lastUpdate >= 3000)
  {
    std::string message;
    if (sensorManager.getReadingsJson(message))
    {
      mesh.publish(
          reinterpret_cast<const uint8_t *>(message.c_str()), message.length());
    }

    lastUpdate = currentTime;
  }
}

// put function definitions here:
void printMessage(const MeshMessage &message,
                  const MeshReceiveInfo &receiveInfo, void *context)
{
  (void)context;
  Serial.printf("Received from %02X:%02X:%02X:%02X:%02X:%02X, RSSI ",
                receiveInfo.sender[0], receiveInfo.sender[1],
                receiveInfo.sender[2], receiveInfo.sender[3],
                receiveInfo.sender[4], receiveInfo.sender[5]);
  if (receiveInfo.rssi == static_cast<int8_t>(-128))
  {
    Serial.print("unavailable");
  }
  else
  {
    Serial.printf("%d dBm", receiveInfo.rssi);
  }
  Serial.printf(", origin %02X:%02X:%02X:%02X:%02X:%02X, sequence %u, ttl %u, hops %u",
                message.origin[0], message.origin[1], message.origin[2],
                message.origin[3], message.origin[4], message.origin[5],
                message.sequence, message.ttl, message.hops);
  Serial.print(" | message: ");
  for (size_t i = 0; i < message.payloadLength; ++i)
  {
    Serial.write(message.payload[i]);
  }
  Serial.println();
}

#endif
