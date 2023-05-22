## Microphone Data Processing

That provides a way to capture and process audio data from a microphone connected to an Arduino board.

### Dependencies

* WiFiNINA
* PDM

### Configuration

The following configuration variables can be adjusted to fine-tune the beat and onset detection algorithm:

* `bufferSize`: The size of the sample buffer used for storing audio data. It is set to 512.
* `windowSize`: The size of the window used for onset detection. It determines the number of previous samples considered when evaluating the onset. It is set to 40.
* `bassWindowSize`: The size of the window used for bass drop detection. It determines the number of consecutive samples used to calculate the bass power. It is set to 2.
* `alpha`: Smoothing coefficient for the exponential moving average used to smooth the audio data. It is set to 0.9.
* `beta`: Smoothing coefficient for the current sample used in the exponential moving average. It is set to 0.1.
* `onsetThreshold`: The threshold for detecting onsets. If the current sample is greater than this threshold multiplied by the corresponding previous sample within the window, an onset is detected. It is set to 0.2.
* `peakThreshold` : The threshold for detecting peaks. If the smoothed value of the current sample is greater than this threshold, a peak is detected. It is set to 0.01.
* `bassDropThreshold` : The threshold for detecting bass drops. If the bass power within the bass window is greater than this threshold multiplied by the previous bass power, a bass drop is detected. It is set to 0.001.
* `silenceThreshold` : The threshold for silence detection. It is not explicitly used in the code but is defined for reference. It is set to 0.05.

### Variables

* `sampleBuffer`: An array of shorts used to store the audio samples received from the PDM microphone. It has a size of bufferSize and is initialized with zeros.
* `smoothedData` : An array of floats used to store the smoothed audio data. It has a size of bufferSize and is initialized with zeros.
* `prevBassPower` : A float variable that holds the previous bass power value used for bass drop detection. It is initialized to 0.0.
* `bassDropDetected` : A boolean variable indicating whether a bass drop has been detected.
* `peakDetected` : A boolean variable indicating whether a peak has been detected.
* `onsetDetected` : A boolean variable indicating whether an onset has been detected.

### Functions

* The `micSetup()` function initializes the serial communication and sets up the PDM interface to receive audio data. It also sets the sample rate to 16kHz.

```cpp
void micSetup() {
  Serial.begin(9600);
  PDM.onReceive(onPDMdata);
  if (!PDM.begin(1, 16000)) {
    Serial.println("Failed to start PDM!");
    while (true);
  }
}
```

* The `onPDMdata()` function is called whenever new audio data is available. It reads the data from the PDM interface and passes it to the `processSamples()` function:

```cpp
void onPDMdata() {
  int bytesAvailable = PDM.available();
  int bytesRead = PDM.read(sampleBuffer, bytesAvailable);
  processSamples(sampleBuffer, bytesRead / 2);
}
```

* The `processSamples()` function processes the audio data and detects beats and onsets:

```cpp
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
        bassDropDetected = true;
      }
      else{
        bassDropDetected = false;
      }
      prevBassPower = bassPower / bassWindowSize;
    }

    // Peak detection logic
    if (smoothedValue > peakThreshold) {
      peakDetected = true;
    }
    else{
      peakDetected = false;
    }

    // Onset detection logic
    if (i >= windowSize && smoothedValue > onsetThreshold * smoothedData[i - windowSize]) {
      onsetDetected = true;
    }
    else{
      onsetDetected = false;
    }

    smoothedData[i] = smoothedValue;
  }
}
```

* The `getValues()` function can be used to print the values of `beatCounter` and `peakCounter` to the serial monitor:

```cpp
void getValues(){
  Serial.print(bassDropDetected);
  Serial.print(",");
  Serial.print(peakDetected);
  Serial.print(",");
  Serial.print(onsetDetected);
  Serial.println();
}
```




