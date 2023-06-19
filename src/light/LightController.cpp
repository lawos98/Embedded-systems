#include <WiFiNINA.h>
#include "LightController.h"
#include "visualizer/visualizer.h"
#include "Parameters.h"

// Maximum number of devices (change according to your needs)
#define MAX_DEVICES 10 

int timeBetweenRequests = 30;

int whiteColor[3] = {255,255,255};

uint16_t yeelightPort = 55443;
WiFiClient clients[MAX_DEVICES];

int convertRGBtoInt(int* averageColor) {
  unsigned int color = ((unsigned int)averageColor[0] << 16) | ((unsigned int)averageColor[1] << 8) | (unsigned int)averageColor[2];
  return color;
}

bool checkWiFi(const char* ssid, const char* pass) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connected to WiFi. Attempting to reconnect...");
    for (int attempts = 0; attempts < 5; attempts++) {
      if (WiFi.begin(ssid, pass) == WL_CONNECTED) {
        Serial.println("Connected to WiFi");
        return true;
      }
      Serial.println("Connecting to WiFi...");
      delay(5000);
    }
    return false;
  } else {
    Serial.println("WiFi connection is OK. Check Yeelight IP, port, and LAN Control setting.");
    return true;
  }
}

bool sendRequest(int deviceId, String payload) {
  if (!clients[deviceId].connected()) {
    Serial.println("Reconnecting client " + String(deviceId));
    if (!clients[deviceId].connect(params.deviceIPs[deviceId].c_str(), yeelightPort)) {
      return false;
    }
  }
  clients[deviceId].println(payload);
  return true;
}

String buildPayload(const char* method, const String params[4]) {
  String payload = "{\"id\":1,\"method\":\"";
  payload += method;
  payload += "\",\"params\":[";
  for (int i = 0; i < 4; i++) {
    payload += params[i];
    if (i != 3) {
      payload += ',';
    }
  }
  payload += "]}\r\n";
  return payload;
}

void setBulbColor(int* color, int time, int deviceId){
  String params[] = { String(convertRGBtoInt(color)), "\"smooth\"", String(time), "" };
  String payload = buildPayload("set_rgb", params);
  delay(timeBetweenRequests);
  if (!sendRequest(deviceId, payload)) {
    Serial.println("Failed to set bulb color");
  }
}

void setBulbBrightness(int brightness, int time, int deviceId){
  String params[] = { String(brightness), "\"smooth\"", String(time), "" };
  String payload = buildPayload("set_bright", params);
  delay(timeBetweenRequests);
  if (!sendRequest(deviceId, payload)) {
    Serial.println("Failed to set bulb brightness");
  }
}

void setBulbPower(bool power, int time, int deviceId){
  String params[] = { power ? "\"on\"" : "\"off\"", "\"smooth\"", String(time), "" };
  String payload = buildPayload("set_power", params);
  delay(timeBetweenRequests);
  if (!sendRequest(deviceId, payload)) {
    Serial.println("Failed to set bulb power");
  }
}

void checkLights(){
  Serial.println("Checking light devices connection...");
  for (unsigned int i = 0; i < sizeof(params.deviceIPs) / sizeof(params.deviceIPs[0]); i++) {
    if (!sendRequest(i, "")) {
      Serial.println("Failed to connect to light device.");
    }
  }
  for (unsigned int i = 0; i < sizeof(params.deviceIPs) / sizeof(params.deviceIPs[0]); i++) {
    setBulbPower(false, 1000, i);
    setBulbBrightness(100, 1000, i);
    setBulbColor(whiteColor, 1000, i);
  }
  delay(1000);
  for (unsigned int i = 0; i < sizeof(params.deviceIPs) / sizeof(params.deviceIPs[0]); i++) {
    setBulbPower(true, 1000, i);
  }
}

void lightChange(int time) {
  int averageColor[3];
  for (unsigned int i = 0; i < sizeof(params.deviceIPs) / sizeof(params.deviceIPs[0]); i++) {
    getAverageColor(params.coordinates[i][0], params.coordinates[i][1], params.coordinates[i][2], params.coordinates[i][3], averageColor);
    setBulbColor(averageColor, time, i);
  }
}