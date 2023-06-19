# WebConfig

That sets up a simple web server for configuring parameters over a WiFi network.

### Global Variables:

The class includes various global variables to store the WiFi credentials, parameters related to the visualizer, and the WiFi server object. These are initialized in the constructor of the class.

### Functions:

* `WebConfig::WebConfig(...)`: The constructor of the class, which initializes the WiFi server and sets up the necessary parameters.
* `extractFloatParameter(const String& line, const String& paramName)`: This function extracts a floating-point number from a given HTTP GET request line. It searches for the parameter by its name and converts the corresponding value to a float.
* `extractIntParameter(const String& line, const String& paramName)`: Similarly, this function extracts an integer from the HTTP GET request. It utilizes the `extractFloatParameter` function and casts the result to an integer.
* `handleClient()`: This function handles incoming client requests. If a client is connected, it reads the incoming HTTP GET request line by line. When the headers end (a blank line is encountered), it starts responding to the client with HTTP 200 and an HTML page. The HTML page is dynamically generated to include the current values of the parameters, allowing the user to update them. After the HTML page has been sent, the function looks for GET request parameters in the request line and updates the corresponding parameters.
* `begin()`: This function starts the WiFi server and prints the local IP address to the serial monitor. This IP address can be used to access the configuration webpage.
* `checkWiFi()`: This function checks the WiFi connection status and tries to reconnect if the connection is lost.

### Overall

The class WebConfig facilitates a simple web-based interface to modify and display configuration parameters in real-time. These parameters include sound thresholds, predefined colors, and device coordinates. By providing this interface, it's easy to interactively fine-tune the parameters of the system to best match the environment or personal preference. Additionally, the class ensures a stable WiFi connection is maintained and handles any disruptions in the connection.
