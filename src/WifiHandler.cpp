#include <ESP8266WiFi.h>
#include "WifiHandler.h"

WifiHandler::WifiHandler(char* ssid, char* password) {
  _ssid = ssid;
  _password = password;
}

void WifiHandler::setup() {
}

void WifiHandler::loop() {
}

void WifiHandler::connect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);

  unsigned long wifiConnectStart = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (millis() - wifiConnectStart > 5000) {
      return;
    }
  }
}
