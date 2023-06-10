#include <WiFiNINA.h>
#include "light.h"
#include "visualizer/visualizer.h"

// your network SSID (name)
char ssid[] = "Orange-Swiatlowod-2F18";
// your network password
char pass[] = "PXDQEM4AGPM9";
const char* deviceIPs[] = {"192.168.1.48", "192.168.1.86", "192.168.1.51","192.168.1.83"};
const int deviceLeds[] = {1, 1, 1, 50};
const int coordinates[][4] = {{-1, 0, 1, 2}, {-1, 20, 1, 22}, {-1, 40, 1, 42},{-1,0,1,50}};
// Only RGB buls so onlt one dioode per bulb
// Port of your Yeelight bulbs
uint16_t yeelightPort = 55443;
int timeBetweenRequests = 50;

WiFiClient client;

int convertRGBtoInt(int* averageColor) {
  unsigned int color = ((unsigned int)averageColor[0] << 16) | ((unsigned int)averageColor[1] << 8) | (unsigned int)averageColor[2];
  return color;
}

void checkWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connected to WiFi. Attempting to reconnect...");
    while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
      Serial.println("Connecting to WiFi...");
      delay(5000);
    }
    Serial.println("Connected to WiFi");
  } else {
    Serial.println("WiFi connection is OK. Check Yeelight IP, port, and LAN Control setting.");
  }
}

void setBulbColor(int* color,int time,int deviceId){
  if (client.connect(deviceIPs[deviceId], yeelightPort)) {
    // Send "set_rgb" command to Yeelight
    client.print("{\"id\":1,\"method\":\"set_rgb\",\"params\":[");
    client.print(convertRGBtoInt(color));
    client.print(", \"smooth\",");
    client.print(250);
    client.println("]}\r\n");
    client.stop();
    } else {
    Serial.println("Failed to connect to Yeelight. Checking WiFi connection...");
    checkWiFi();
  }
}

void setBulbBrightness(int brightness,int time,int deviceId){
  if (client.connect(deviceIPs[deviceId], yeelightPort)) {
    // Send "set_rgb" command to Yeelight
    client.print("{\"id\":1,\"method\":\"set_bright\",\"params\":[");
    client.print(brightness);
    client.print(", \"smooth\",");
    client.print(time);
    client.println("]}\r\n");
    client.stop();
    } else {
    Serial.println("Failed to connect to Yeelight. Checking WiFi connection...");
    checkWiFi();
  }
}

void setBulbPower(bool power,int time,int deviceId){
  if (client.connect(deviceIPs[deviceId], yeelightPort)) {
    client.print("{\"id\":1,\"method\":\"set_power\",\"params\":[\"");
    if(power){
      client.print("on");
    }
    else{
      client.print("off");
    }
    client.print("\", \"smooth\", ");
    client.print(time);
    client.println("]}\r\n");
    client.stop();
    } 
  else{
    Serial.println("Failed to connect to Yeelight. Checking WiFi connection...");
    checkWiFi();
  }
}

void setLedStripSegmentColor(int* color, int time, int deviceId, int segmentId){
  if (client.connect(deviceIPs[deviceId], yeelightPort)) {
    client.print("{\"id\":1,\"method\":\"set_segment_color\",\"params\":[");
    client.print(segmentId);
    client.print(", ");
    client.print(convertRGBtoInt(color));
    client.print(", \"smooth\",");
    client.print(time);
    client.println("]}\r\n");
    client.stop();
  } else {
    Serial.println("Failed to connect to LED strip. Checking WiFi connection...");
    checkWiFi();
  }
}

void setLedStripBrightness(int brightness, int time, int deviceId) {
  if (client.connect(deviceIPs[deviceId], yeelightPort)) {
    client.print("{\"id\":1,\"method\":\"set_bright\",\"params\":[");
    client.print(brightness);
    client.print(", \"smooth\",");
    client.print(time);
    client.println("]}\r\n");
    client.stop();
  } else {
    Serial.println("Failed to connect to LED strip. Checking WiFi connection...");
    checkWiFi();
  }
}

void setLedStripPower(bool power, int time, int deviceId) {
  if (client.connect(deviceIPs[deviceId], yeelightPort)) {
    client.print("{\"id\":1,\"method\":\"set_power\",\"params\":[\"");
    if(power){
      client.print("on");
    } else {
      client.print("off");
    }
    client.print("\", \"smooth\", ");
    client.print(time);
    client.println("]}\r\n");
    client.stop();
  } else {
    Serial.println("Failed to connect to LED strip. Checking WiFi connection...");
    checkWiFi();
  }
}

void lightSetup() {
    Serial.println("Connecting to WiFi...");
    while (!Serial){
        Serial.println("Waiting for Serial connection...");
    }
    // attempt to connect to WiFi network
    while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
        Serial.println("Connecting to WiFi...");
        delay(5000);
    }
    Serial.println("Connected to WiFi");
}

void checkLights(){
  Serial.println("Checking light devices connection...");
  for (unsigned int i = 0; i < sizeof(deviceIPs) / sizeof(deviceIPs[0]); i++) {
    if (client.connect(deviceIPs[i], yeelightPort)) {
      int whiteColor[3] = {255,255,255};
      if (deviceLeds[i] == 1) {
        setBulbColor(whiteColor, 500, i);
        setBulbPower(true, 500, i);
      } else {
        for (int j = 0; j < deviceLeds[i]; j++) {
          setLedStripSegmentColor(whiteColor, 500, i, j);
        }
        setLedStripPower(true, 500, i);
      }
      client.stop();
      delay(timeBetweenRequests);
    } else {
      Serial.println("Failed to connect to light device. Checking WiFi connection...");
      checkWiFi();
    }
  }
  delay(500);
  for (unsigned int i = 0; i < sizeof(deviceIPs) / sizeof(deviceIPs[0]); i++) {
    if (client.connect(deviceIPs[i], yeelightPort)) {
      if (deviceLeds[i] == 1) {
        setBulbPower(false, 500, i);
      } else {
        setLedStripPower(false, 500, i);
      }     
      client.stop();
      delay(timeBetweenRequests);
    } else {
      Serial.println("Failed to connect to light device. Checking WiFi connection...");
      checkWiFi();
    }
  }
  delay(500);
  for (unsigned int i = 0; i < sizeof(deviceIPs) / sizeof(deviceIPs[0]); i++) {
    if (client.connect(deviceIPs[i], yeelightPort)) {
      if (deviceLeds[i] == 1) {
        setBulbPower(true, 500, i);
      } else {
        setLedStripPower(true, 500, i);
      }  
      client.stop();
      delay(timeBetweenRequests);
    } else {
      Serial.println("Failed to connect to light device. Checking WiFi connection...");
      checkWiFi();
    }
  }
}

void lightChange(int time) {
  int color[3];
  for (unsigned int i = 0; i < sizeof(deviceIPs) / sizeof(deviceIPs[0]); i++) {
    if(deviceLeds[i]==1){
      getAverageColor(coordinates[i][0], coordinates[i][1], coordinates[i][2], coordinates[i][3], color);
      if (client.connect(deviceIPs[i], yeelightPort)) {
        setBulbColor(color, time, i);
        client.stop();
        delay(timeBetweenRequests);
      } else{
          Serial.println("Failed to connect to Yeelight. Checking WiFi connection...");
          checkWiFi();
      }
    } else {
      int x1 = coordinates[i][0], y1 = coordinates[i][1], x2 = coordinates[i][2], y2 = coordinates[i][3];
      int step;
      if(abs(x1-x2) > abs(y1-y2)){
        step = abs(x1-x2)/deviceLeds[i];
        for (int x = x1; x < x2; x+=step) {
          getAverageColor(x, y1, x+step, y2, color);
          setLedStripSegmentColor(color, time, i, x);
        }
      } else {
        step = abs(y1-y2)/deviceLeds[i];
        for (int y = y1; y < y2; y+=step) {
          getAverageColor(x1, y, x2, y+step, color);
          setLedStripSegmentColor(color, time, i, y);
        }
      }
    }
  }
}