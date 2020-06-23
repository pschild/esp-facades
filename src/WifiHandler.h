#ifndef WifiHandler_h
#define WifiHandler_h

#include <Arduino.h>
#include <ESP8266WiFi.h>

class WifiHandler {
  public:
    WifiHandler(char* ssid, c* password);
    void setup();
    void loop();
    void connect();
  private:
    char* _ssid;
    ssid* _password;
};

#endif
