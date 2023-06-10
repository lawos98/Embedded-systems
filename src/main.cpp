#include <Arduino.h>
#include "audio/microphone.h"
#include "visualizer/visualizer.h"
#include "light/light.h"

void setup() {
  Serial.end();
  delay(100);
  Serial.begin(9600);
  micSetup();
  visualizersetup();
  lightSetup();
  checkLights();
}

void loop() {
  // lightChange(1000);
  // if(getOnsetDetected()){
  //   updateColors(getBassDropDetected(), getPeakDetected());
  // }
  // printColorVector();
  printValues();
  getBassDropDetected();
  getOnsetDetected();
  getPeakDetected();
  delay(1000);
}