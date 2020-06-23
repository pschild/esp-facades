#ifndef WifiHandler_h
#define WifiHandler_h

#include <Arduino.h>
#include <ESP8266WiFi.h>

class WifiHandler {
  public:
    WifiHandler(String ssid, String password);
    void setup();
    void loop();
    void connect();
  private:
    String _ssid;
    String _password;
};

#endif
