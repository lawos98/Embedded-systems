#Visualizer

This code snippet is part of an audio visualizer that utilizes a concept of 'cursors' to orchestrate a visual representation of audio by dynamically changing color schemes based on certain sound characteristics, like bass drops or peaks. The idea is to generate a compelling light show that responds to music or other sounds, providing an immersive sensory experience.

### Global Variables:

Firstly, the required libraries and parameters are included using the `#include` directive. `WiFiNINA` is a library that allows communication over WiFi, and `PDM` handles Pulse Density Modulation, which is a method to convert analog signals into digital. The `Parameters.h` file is probably custom-made for this application, containing a variety of configurations.

The file introduces a series of global variables, such as cursor position, speed, size, and color, to control the behavior of the visualizers and synchronize them with the audio features.

### Functions:

* `getAverageColor(int x1, int y1, int x2, int y2, int* averageColor)`: This function calculates the average color within a specified rectangular region defined by two points (x1, y1) and (x2, y2). It iterates over the area, calculating the radial distance from the center to each pixel. It then uses this radial distance to index into a predefined array of colors (`params.predefinedColors`). It adds the RGB components of the color to running totals, and then calculates the average color across all pixels by dividing by the total count of pixels.
* `addCursor(int type)`: This function adds a new cursor of the provided type to the system. Depending on the type, the cursor could move from the beginning to the end of the visualizer (type 1) or from the end to the beginning (type 2). The function also imposes restrictions on how frequently cursors of a certain type can be added, using a spawn time for each type.
* `removeCursor(int index)`: This function deletes the cursor at the specified index. All cursors following the one being removed are then shifted back in the arrays to fill the gap.
* `updateColors(bool bassDropDetected, bool peakDetected)`: This function is responsible for managing the visual effects in response to the audio features. If a bass drop or a peak in the audio is detected, it adds a new cursor. Then, it updates each cursor's position and modifies the color at each cursor's position. The color change is done by setting the `params.colorVector` at the current position of each cursor to the color of the cursor.
* `visualizersetup()`: This function initializes the color vector, setting all elements to zero. This might be used at the start of the program or whenever a reset of the visualizer is required.
* `printColorVector()`: This function prints the current state of the color vector to the serial monitor. It's a debug function, used to observe the inner state of the program during execution.

### In summary:

This code provides the logic for a dynamic audio visualizer that changes colors in response to the music. The primary driver of these changes are the cursors, which move across the visualizer, changing colors as they are influenced by the different characteristics of the audio, such as bass drops and peaks. By synchronizing the movement and color changes of these cursors with the audio, a compelling light show is created.



