#include <Arduino.h>
#include "audio/microphone.h"

void setup() {
  micSetup();
}

void loop() {
  getValues();
  delay(200);
}