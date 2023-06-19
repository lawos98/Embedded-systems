# Light Controller

This part of your code is responsible for controlling WiFi light bulbs in response to the processed audio data. It communicates with the bulbs via their network API, sends commands to change their color and brightness, and maintains the network connection. Let's delve into the specifics:

### Global Variables:

* The required libraries and parameters are imported, such as `WiFiNINA` for WiFi connection, `LightController` and `visualizer` which are responsible for handling light controls and creating visualizations, and `Parameters` which handles the storage of various parameters.
* Constants and variables for bulb control are defined, such as the default white color (`whiteColor`), port for Yeelight bulbs (`yeelightPort`), and an array of WiFi clients (`clients`).

 ### Functions:

* `convertRGBtoInt(int* averageColor)`: This function converts an RGB array to a single integer value that can be used to set the color of a bulb.
* `checkWiFi(const char* ssid, const char* pass)`: This function checks the WiFi connection status and tries to reconnect if the Arduino is not connected.
* `sendRequest(int deviceId, String payload)`: This function sends a given payload to a specified light bulb. It reconnects to the bulb if the WiFi client is not currently connected.
* `buildPayload(const char* method, const String params[4])`: This function builds a JSON-formatted payload for a specified command and an array of parameters. This payload can then be sent to a bulb.
* `setBulbColor(int* color, int time, int deviceId)`: This function sets the color of a specified bulb to a given RGB color over a certain period of time.
* `setBulbBrightness(int brightness, int time, int deviceId)`: This function sets the brightness of a specified bulb to a given level over a certain period of time.
* `setBulbPower(bool power, int time, int deviceId)`: This function turns a specified bulb on or off over a certain period of time.
* `checkLights()`: This function checks the connection to each light device. It also initializes each light device by turning it off, setting its brightness to 100, setting its color to white, and then turning it back on.
* `lightChange(int time)`: This function updates the color of each light bulb based on the average color of a region of the visualization. The regions are defined by the `params.coordinates` array.

### Overall, the code:

1. Maintains the WiFi connection and connection to each light bulb.
2. Sends commands to the light bulbs to change their color, brightness, and power state.
3. Updates the color of each light bulb based on the average color of a region of the music visualization.
4. Provides functions to build the required JSON payloads for the bulb API and convert RGB color arrays into a format that can be used by the bulb API.
