#include <WiFiNINA.h>
#include <PDM.h>
#include "microphone.h"

static const char CHANNELS = 1;
// Sampling frequency
static const int FREQUENCY = 16000;
// Number of PDM samples

// Buffer to read samples into, each sample is 16-bits
short sampleBuffer[512] = {0};

// Number of audio samples read
volatile int samplesRead;

// Number of filter coefficients
const int N = 16;

// Filter coefficients
float w[N] = {0};

// Input buffer
float x[N] = {0};


// Step size
const float mu = 0.0000002;

void onPDMdata() {
  // Query the number of available bytes
  int bytesAvailable = PDM.available();

  // Read into the sample buffer
  PDM.read(sampleBuffer, bytesAvailable);

  // 16-bit, 2 bytes per sample
  samplesRead = bytesAvailable / 2;
}

void microphoneInit() {
  while (!Serial){}
  PDM.onReceive(onPDMdata);
  PDM.setGain(-20); // Optionally set the gain
  if (!PDM.begin(CHANNELS, FREQUENCY)) {
    Serial.println("Failed to start PDM!");
    while (1);
  }
}

void microphoneRead() {
  if(samplesRead) {  // Wait for samples to be read
    // Apply LMS noise cancellation
    for (int i = 0; i < samplesRead; i++) {
      // Shift input buffer
      for (int j = N-1; j > 0; j--) {
        x[j] = x[j-1];
      }
      x[0] = sampleBuffer[i];
      
      // Calculate output
      float y = 0;
      for (int j = 0; j < N; j++) {
        y += w[j] * x[j];
      }
      
      // Update filter coefficients
      float e = sampleBuffer[i] - y;
      for (int j = 0; j < N; j++) {
        w[j] += mu * e * x[j];
      }
      
      // Apply low-pass filter
      y = 0.9 * y + 0.1 * sampleBuffer[i];
      
      // Write filtered data to serial port
      Serial.println(y);
    }
    samplesRead = 0;
  }
}