## Microphone Data Processing

That provides a way to capture and process audio data from a microphone connected to an Arduino board.

### Dependencies

* WiFiNINA
* PDM

### Configuration

The following configuration variables can be adjusted to fine-tune the beat and onset detection algorithm:

* `bufferSize`: The size of the audio buffer in samples
* `sampleRate`: The sample rate of the audio data
* `samplesPerBeat`: The number of audio samples per beat. It's calculated as sampleRate / 4, assuming a tempo of 4 beats per measure.
* `onsetThreshold`: The minimum amplitude of an audio sample required to trigger an "onset", which is a sudden change in the audio signal that may indicate the beginning of a beat or musical phrase.
* `bassDropThreshold`: A threshold for detecting "bass drops", which are sudden decreases in the bass frequency content of the audio that may indicate a musical drop or breakdown.
* `peakThreshold`: The threshold for detecting a peak in the smoothed signal.

### Variables

* `sampleBuffer`: An array that stores the audio samples.
* `onsetSampleCounter`: A counter that keeps track of the number of samples since the last onset.
* `beatCounter`: A counter that keeps track of the number of beats detected so far.
* `alpha and beta`: Coefficients used to smooth the incoming audio signal.
* `windowSize`: The size of the window used to find local maxima in the smoothed signal.
* `prevMaxValue` and `prevMaxPos`: The maximum value and position of the previous local maximum in the smoothed signal, used to detect peaks in the signal.
* `peakCounter`: A counter that keeps track of the number of peaks detected so far.

### Functions

* The `micSetup()` function initializes the serial communication and sets up the PDM interface to receive audio data. It also sets the sample rate to 16kHz.

```cpp
void micSetup() {
    Serial.begin(9600);
    PDM.onReceive(onPDMdata);
    if (!PDM.begin(1, sampleRate)) {
        Serial.println("Failed to start PDM!");
        while (1);
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
```

* The `getValues()` function can be used to print the values of `beatCounter` and `peakCounter` to the serial monitor:

```cpp
void getValues(){
    Serial.print(beatCounter);
    Serial.print(",");
    Serial.print(peakCounter);
    Serial.println();
}
```




