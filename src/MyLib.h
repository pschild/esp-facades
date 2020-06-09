#ifndef MyLib_h
#define MyLib_h

#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

class MyLib {
  public:
    MyLib(char* brokerIP, char* clientName, WiFiClient wifiClient);
    void setup();
    void loop();
    void reconnect();
  private:
    char* _brokerIP;
    char* _clientName;
    PubSubClient* _mqttClient;
};

#endif
