#include <WiFiNINA.h>
#include <PDM.h>
#include "AudioAnalyzer.h"
#include "Parameters.h"

constexpr int bufferSize = 1024;
constexpr int windowSize = 40;
constexpr float alpha = 0.98;
constexpr float beta = 1.0 - alpha;


float smoothedData[bufferSize] = {0};
double prevBassPower = 0.0;
short sampleBuffer[bufferSize] = {0};

int bassDropDetected = 0;
int peakDetected = 0;
int onsetDetected = 0;

float bassAvg = 0;
float bassHigh = 0;
float decayFactor = 0.99;

float prevSample = 0.0;

void processSamples(short *buffer, int numSamples) {
  for (int i = 0; i < numSamples; i++) {
    float currentBassSample = abs(buffer[i]);
    float currentSample = buffer[i] / 32768.0;
    float smoothedValue = alpha * smoothedData[i] + beta * currentSample;


    if (currentBassSample < params.silenceThreshold) {
      continue;
    }

    // Onset detection
    if (i >= windowSize && smoothedValue > params.onsetThreshold * smoothedData[i - windowSize]) {
      onsetDetected++;
    }

    float bassComponent = alpha * prevBassPower + beta * currentBassSample;
    prevBassPower = bassComponent;
    bassAvg = alpha * bassAvg + beta * bassComponent;
    bassHigh = max(bassComponent, bassHigh * decayFactor);

    // Bass Drop detection
    if (bassComponent > params.bassDropThreshold * bassAvg && bassComponent >= bassHigh) {
      bassDropDetected++;
    }
    // Peak detection
    else if (bassComponent > params.peakThreshold * bassAvg) {
      peakDetected++;
    }

    smoothedData[i] = smoothedValue;
  }
}

void onPDMdata() {
  int bytesAvailable = PDM.available();
  int bytesRead = PDM.read(sampleBuffer, bytesAvailable);
  processSamples(sampleBuffer, bytesRead/2);
}

bool checkBassDropDetected(){
  int temp = bassDropDetected;
  bassDropDetected = 0;
  return temp>0;
}

bool checkPeakDetected(){
  int temp = peakDetected;
  peakDetected = 0;
  return temp>0;
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