#include <WiFiNINA.h>
#include <PDM.h>
#include "microphone.h"

constexpr int bufferSize = 1024;
constexpr int windowSize = 40;
constexpr int bassWindowSize = 2;
constexpr float alpha = 0.9;
constexpr float beta = 0.1;
constexpr float onsetThreshold = 0.2;
constexpr float peakThreshold = 0.01;
constexpr float bassDropThreshold = 0.1;
constexpr float silenceThreshold = 0.05;


float smoothedData[bufferSize] = {0};
float prevBassPower = 0.0;
short sampleBuffer[bufferSize] = {0};

int bassDropDetected = 0;
int peakDetected = 0;
int onsetDetected = 0;

void processSamples(short *buffer, int numSamples) {
  for (int i = 0; i < numSamples; i++) {
    float currentSample = buffer[i] / 32768.0;
    float smoothedValue = alpha * smoothedData[i] + beta * currentSample;

    // Bass Drop detection
    if (i % bassWindowSize == 0 && i + bassWindowSize < numSamples) {
      float bassPower = 0.0;
      for (int j = i; j < i + bassWindowSize; j++) {
        float sample = buffer[j] / 32768.0;
        bassPower += sample * sample;
      }
      if (bassPower > bassDropThreshold * bassWindowSize + prevBassPower) {
        bassDropDetected++;
      }
      prevBassPower = bassPower / bassWindowSize;
    }

    // Peak detection logic
    if (smoothedValue > peakThreshold) {
      peakDetected++;
    }

    // Onset detection logic
    if (i >= windowSize && smoothedValue > onsetThreshold * smoothedData[i - windowSize]) {
      onsetDetected++;
    }

    smoothedData[i] = smoothedValue;
  }
}

void onPDMdata() {
  int bytesAvailable = PDM.available();
  int bytesRead = PDM.read(sampleBuffer, bytesAvailable);
  processSamples(sampleBuffer, bytesRead / 2);
}

void printValues(){
  Serial.print(bassDropDetected);
  Serial.print(",");
  Serial.print(peakDetected);
  Serial.print(",");
  Serial.print(onsetDetected);
  Serial.println();
}

int getBassDropDetected(){
  int temp = bassDropDetected;
  bassDropDetected = 0;
  return temp;
}

int getPeakDetected(){
  int temp = peakDetected;
  peakDetected = 0;
  return temp;
}

int getOnsetDetected(){
  int temp = onsetDetected;
  onsetDetected = 0;
  return temp;
}

void micSetup() {
  PDM.onReceive(onPDMdata);
  if (!PDM.begin(1, 16000)) {
    Serial.println("Failed to start PDM!");
    while (true);
  }
}
