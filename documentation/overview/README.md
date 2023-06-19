# A Quick Overview of the Audio Visualizer System

This system is a comprehensive audio visualizer that uses real-time audio input to generate an interactive color display. The process of how it works can be broken down into several stages:

### 1. Audio Detection

The first step is audio detection. Here, the system listens for sound and analyzes it in real-time to detect specific elements, namely:

* `Peak`: This refers to sudden, high-amplitude sound elements often associated with a beat in music.
* `Onset`: This represents the start of a musical note or sound.
* `BassDrop`: This corresponds to a strong and sudden bass sound, often found in electronic music.

### 2. Cursor Generation

Upon detection of these audio elements, the system responds by generating "cursors". These cursors play a central role in the visualizer's color generation process:

* A `peak` detection prompts the generation of a Cursor type 1.
* A `bassDrop` detection prompts the generation of a Cursor type 2.
* An `onset` detection sets the speed of all existing cursors, impacting how quickly the visual display will change.

### 3. Color Vector Generation

The cursors, their positions, and speed collectively generate a color vector. The color vector is a 1-dimensional array where each element corresponds to a color index (pointing to a predefined color).

Examples with diffrent type of music 

* Classic Music

![classic_music](documentation/overview/clasic_music.mp4)

* Rock Music

![rock_music](documentation/overview/rock_music.mkv)

* Techno Music

![rock_music](documentation/overview/techno_music.mp4)

### 4. Color Matrix Generation

The 1-dimensional color vector is then transformed into a 2-dimensional color matrix. This process involves rounding the color vector, mapping its colors to create a matrix that represents the visual display's current state.

![AudioVis](documentation/concept/AudVis.gif)

### 5. Color Averaging for Devices

Each device is associated with a specific section of the matrix. The system calculates the average color for each device's designated section. This is done by summing the colors for all pixels in the region and then dividing by the total number of pixels.

![AudioVis](documentation/concept/matrix.png)

### 6. Color Transmission to Devices

Finally, the averaged colors are sent to their respective devices. These devices then display the color, providing a real-time, interactive visual representation of the audio input.

Overall, this system offers a robust and highly customizable audio-visual experience. It allows for real-time interaction with the audio environment, providing visual feedback that can enhance musical enjoyment and engagement.

