#ifndef WebConfig_h
#define WebConfig_h

#include <WiFiNINA.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include "Parameters.h"

class WebConfig {
  private:
    WiFiServer server;
    Parameters* parameters;
    const char* ssid;
    const char* pass;
    float extractFloatParameter(const String& line, const String& paramName);
    int extractIntParameter(const String& line, const String& paramName);

  public:
    WebConfig(int port, Parameters* params, const char* ssid, const char* pass);

    void handleClient();
    void begin();
    void checkWiFi();
};

#endif