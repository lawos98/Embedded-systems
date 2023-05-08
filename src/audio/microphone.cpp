#include <WiFiNINA.h>
#include <PDM.h>
#include "microphone.h"

const int bufferSize = 512;
short sampleBuffer[bufferSize];
const int sampleRate = 16000;
const int samplesPerBeat = sampleRate / 4;
int onsetThreshold = 1000;
int bassDropThreshold = 1000;
int onsetSampleCounter = 0;
int beatCounter = 0;
const float alpha = 0.9;
const float beta = 0.1;
const int windowSize = 20;
float prevMaxValue = 0.0;
int prevMaxPos = -1;
float peakThreshold = 0.5;

void processSamples(short *buffer, int numSamples) {
  static float smoothedData[bufferSize] = {0};

  for (int i = 0; i < numSamples; i++) {
    smoothedData[i] = alpha * smoothedData[i] + beta * buffer[i];
    if (i > windowSize && i < numSamples - windowSize) {
      float maxValue = 0.0;
      int maxPos = -1;
      for (int j = i - windowSize; j <= i + windowSize; j++) {
        if (smoothedData[j] > maxValue) {
          maxValue = smoothedData[j];
          maxPos = j;
        }
      }
      if (prevMaxPos != -1 && prevMaxPos != maxPos && maxValue - prevMaxValue > peakThreshold) {
        if (onsetSampleCounter > samplesPerBeat / 2) {
          beatCounter++;
          onsetSampleCounter = 0;
        }
      }
      prevMaxValue = maxValue;
      prevMaxPos = maxPos;
    }
    if (smoothedData[i] > onsetThreshold) {
      if (peakCounter > samplesPerBeat) {
        beatCounter++;
        onsetSampleCounter = 0;
      }
    }
    onsetSampleCounter++;
  }
}

void onPDMdata() {
  int bytesAvailable = PDM.available();
  int bytesRead = PDM.read(sampleBuffer, bytesAvailable);
  processSamples(sampleBuffer, bytesRead / 2);
}

void getValues(){
  Serial.print(beatCounter);
  Serial.print(",");
  Serial.print(peakCounter);
  Serial.println();
}

void micSetup() {
  Serial.begin(9600);
  PDM.onReceive(onPDMdata);
  if (!PDM.begin(1, sampleRate)) {
    Serial.println("Failed to start PDM!");
    while (1);
  }
}
