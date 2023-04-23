#include <Arduino.h>
#include "audio/microphone.h"

void setup() {
  microphoneInit();
}

void loop() {
  microphoneRead();
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);  
}