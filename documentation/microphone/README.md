## Microphone Data Processing

That provides a way to capture and process audio data from a microphone connected to an Arduino board.

### Global Variables

* Import of the necessary libraries and parameters: `WiFiNINA` for WiFi connection and `PDM` for Pulse Density Modulation required for microphone input. `AudioAnalyzer` and `Parameters` are likely custom classes handling audio analysis and the storage of various parameters respectively.
* Declaration of constants and variables required for processing audio data, including the buffer for samples (`sampleBuffer`), variables to track and analyze bass levels (`bassDropDetected`, `bassAvg`, etc.), and variables for signal processing (`alpha`, `beta`, `decayFactor`, etc.).

### Functions:

* `processSamples(short *buffer, int numSamples)`: This function analyzes a buffer of sound samples. It first normalizes and smooths the data, discards quiet samples, and then detects 'onsets' (sharp rises in volume), bass drops, and peaks by comparing current and past samples.
* `onPDMdata()`: This function is called whenever PDM data (microphone data) is available. It reads the PDM data into a buffer and then calls processSamples to process it.
* `checkBassDropDetected()`, `checkPeakDetected()`, `getOnsetDetected()`: These functions return whether a bass drop, a peak, or an onset has been detected since the last call to these functions. They also reset the detection variables.
* `micSetup()`: This function sets up the microphone. It tells the PDM library to call `onPDMdata` whenever data is available and starts the PDM system. If the PDM fails to start, it logs an error message and blocks indefinitely.

### Overall, this code:

1. Sets up the microphone and tells it to process audio samples whenever they are available.
2. Processes incoming audio samples by smoothing, normalizing, and filtering them.
   *  `Smoothing`: This process is used to reduce noise and minor fluctuations in the data, making the underlying pattern more visible. In this code, a basic smoothing algorithm, known as exponential smoothing, is applied to the data. This form of smoothing uses a smoothing factor (`alpha`) to calculate a running average where the most recent samples have a greater effect on the smoothed value. This is achieved by multiplying the smoothing factor with the previous smoothed data and adding it to the current sample multiplied by `(1 - alpha)`. The line of code doing this is `float smoothedValue = alpha * smoothedData[i] + beta * currentSample`;
   *  `Normalizing`: Normalization is a process that adjusts values measured on different scales to a common scale. In this code, audio samples which are usually in the range of -32768 to 32767 (16-bit signed integers) are divided by 32768, normalizing them to a range between -1.0 and 1.0. This is shown in float currentSample = buffer[i] / 32768.0;.
   *  `Filtering`: Filters are used to remove unwanted components or features from the data. In this code, a simple low-pass filter is used to extract the bass component of the audio. A low-pass filter allows signals with a frequency lower than a certain cutoff frequency to pass through and attenuates frequencies higher than the cutoff frequency. This is particularly useful for detecting bass drops, as they are characterized by low frequencies. The line of code that applies the low-pass filter to the smoothed value is float bassComponent = alpha * prevBassPower + beta * currentBassSample;.
3. Continuously checks for 'onsets', 'peaks', and 'bass drops' in the audio data.
4. Provides a way to check whether a bass drop, a peak, or an onset has been detected since the last check.



