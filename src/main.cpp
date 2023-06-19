#include <Arduino.h>
#include "audio/AudioAnalyzer.h"
#include "visualizer/visualizer.h"
#include "light/light.h"
#include "web/WebConfig.h"
#include "Parameters.h"

const char ssid[] = "Orange-Swiatlowod-2F18";
const char pass[] = "PXDQEM4AGPM9";

Parameters params = {
  .bassDropThreshold = 2.0F,
  .peakThreshold = 1.6F,
  .onsetThreshold = 1.3F,
  .silenceThreshold = 500.0F,
  .predefinedColors = {
    {204, 0, 255},
    {0, 204, 255},
    {255, 0, 0}
  },
  .deviceIPs = {
    "192.168.1.48",
    "192.168.1.86",
    "192.168.1.51"
  },
  .deviceLeds = {1, 1, 1},
  .coordinates = {
    {-1, 0, 1, 2},
    {-1, 10, 1, 12},
    {-1, 20, 1, 22}
  }
};

WebConfig webConfig(80, &params, ssid, pass);

void setup() {
  Serial.end();
  Serial.begin(9600);

  while (!Serial)
  {
    /* code */
  }

  webConfig.checkWiFi();
  webConfig.begin();
  micSetup();

  visualizersetup();
  checkLights();
}

unsigned long lastLightChange = 0;
unsigned long lastUpdate = 0;
int onsetDetectionCounter = 0;
unsigned long delayTime = 0;


void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastLightChange >= 6000) {
    lightChange(delayTime);
    lastLightChange = currentMillis;
  }
  onsetDetectionCounter=getOnsetDetected();
  if(onsetDetectionCounter>0){
    updateColors(checkBassDropDetected(), checkPeakDetected());
  }
  
  webConfig.handleClient();
  printColorVector();
  delayTime=min(max((currentMillis-lastUpdate)*500/max(onsetDetectionCounter,1),20),1000);
  delay(delayTime);
  lastUpdate = currentMillis;
}