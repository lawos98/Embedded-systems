#include "WebConfig.h"

WebConfig::WebConfig(int port, Parameters* params, const char* ssid, const char* pass)
    : server(port), parameters(params), ssid(ssid), pass(pass) {}


float WebConfig::extractFloatParameter(const String& line, const String& paramName) {
    int start = line.indexOf(paramName + "=");
    if (start != -1) {
        int end = line.indexOf("&", start);
        if (end == -1) {
            end = line.length();
        }
        return line.substring(start + paramName.length() + 1, end).toFloat();
    }
    return 0.0;
}

int WebConfig::extractIntParameter(const String& line, const String& paramName) {
    return (int) extractFloatParameter(line, paramName);
}

void WebConfig::handleClient() {
    WiFiClient client = server.available();

    if (client) {
      String currentLine = "";
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();

          if (c == '\n') {
            if (currentLine.length() == 0) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();

              client.print("<h1>Configuration Parameters</h1>");
              client.print("<form method=\"get\">");
              client.print("Bass Drop Threshold: <input type=\"text\" name=\"bassDropThreshold\" value=\"" + String(parameters->bassDropThreshold) + "\"><br>");
              client.print("Peak Threshold: <input type=\"text\" name=\"peakThreshold\" value=\"" + String(parameters->peakThreshold) + "\"><br>");
              client.print("Onset Threshold: <input type=\"text\" name=\"onsetThreshold\" value=\"" + String(parameters->onsetThreshold) + "\"><br>");
              
              client.print("Silence Threshold: <input type=\"text\" name=\"silenceThreshold\" value=\"" + String(parameters->silenceThreshold) + "\"><br>");
              
              for (int i = 0; i < NUM_COLORS; i++) {
                client.print("Predefined Color " + String(i) + ":(RGB)<br>");
                for (int j = 0; j < NUM_CHANNELS; j++) {
                  client.print("<input type=\"text\" name=\"color" + String(i) + "Channel" + String(j) + "\" value=\"" + String(parameters->predefinedColors[i][j]) + "\">");
                }
                String color = "rgb(" + String(parameters->predefinedColors[i][0]) + ", " + String(parameters->predefinedColors[i][1]) + ", " + String(parameters->predefinedColors[i][2]) + ")";
                client.print("<div style=\"width:50px; height:50px; background-color:" + color + "\"></div>");
                client.print("<br>");
              }

              for (int i = 0; i < NUM_DEVICES; i++) {
                client.print("Device Coordinate " + String(i) + "(x1,y1,x2,y2):<br>");
                for (int j = 0; j < NUM_COORD_PARAMS; j++) {
                  client.print("<input type=\"text\" name=\"coordinate" + String(i) + "Param" + String(j) + "\" value=\"" + String(parameters->coordinates[i][j]) + "\">");
                }
                client.print("<br>");
              }

              client.print("<br>"); 

              client.print("<input type=\"submit\" value=\"Update\">");
              client.print("</form>");

              client.print("<h2>Current Color Vector</h2>");
              for (int i = 0; i < VECTOR_SIZE; i++) {
                String color = "rgb(" + String(parameters->predefinedColors[params.colorVector[i]][0]) + ", " + String(parameters->predefinedColors[params.colorVector[i]][1]) + ", " + String(parameters->predefinedColors[params.colorVector[i]][2]) + ")";
                client.print("<div style=\"width:50px; height:50px; background-color:" + color + "\"></div>");
              }

              client.println();
              break;
            } else {
              currentLine = "";
            }
          } else if (c != '\r') {
            currentLine += c;
          } else if (currentLine.startsWith("GET /?bassDropThreshold=")) {
            parameters->bassDropThreshold = extractFloatParameter(currentLine, "bassDropThreshold");
            parameters->peakThreshold = extractFloatParameter(currentLine, "peakThreshold");
            parameters->onsetThreshold = extractFloatParameter(currentLine, "onsetThreshold");
            parameters->silenceThreshold = extractFloatParameter(currentLine, "silenceThreshold");

            // predefinedColors
            for (int i = 0; i < NUM_COLORS; i++) {
              for (int j = 0; j < NUM_CHANNELS; j++) {
                parameters->predefinedColors[i][j] = extractIntParameter(currentLine, "color" + String(i) + "Channel" + String(j));
              }
            }

            // coordinates
            for (int i = 0; i < NUM_DEVICES; i++) {
              for (int j = 0; j < NUM_COORD_PARAMS; j++) {
                parameters->coordinates[i][j] = extractIntParameter(currentLine, "coordinate" + String(i) + "Param" + String(j));
              }
            }





          }
        }
      }

      delay(1);
      client.stop();
    }
}

void WebConfig::begin() {
  server.begin();

  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
}

void WebConfig::checkWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connected to WiFi. Attempting to reconnect...");
    while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
      Serial.println("Connecting to WiFi...");
      delay(5000);
    }
    Serial.println("Connected to WiFi");
  } else {
    Serial.println("WiFi connection is OK. Check Yeelight IP, port, and LAN Control setting.");
  }
}
