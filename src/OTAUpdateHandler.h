#ifndef OTAUpdateHandler_h
#define OTAUpdateHandler_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>

class OTAUpdateHandler {
  public:
    OTAUpdateHandler(String updateServerIP, String version);
    void setup();
    void loop();
    void checkForUpdate();
    void startUpdate();
    void setInterval(long interval);
  private:
    String _updateServerIP;
    String _version;
    long _updateInterval;
    long _lastUpdateCheck;
    String buildEnpointUrl();
};

#endif
