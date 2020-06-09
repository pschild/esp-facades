// #include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "MyLib.h"

MyLib::MyLib(char* brokerIP, char* clientName, WiFiClient wifiClient) {
  _brokerIP = brokerIP;
  _clientName = clientName;
  _mqttClient = new PubSubClient(wifiClient);
}

void MyLib::setup() {
  _mqttClient->setServer(_brokerIP, 1883);
}

void MyLib::loop() {
  if (!_mqttClient->connected()) {
    reconnect();
  }

  _mqttClient->loop();
}

void MyLib::reconnect() {
  while (!_mqttClient->connected()) {
    Serial.print("Reconnecting...");

    if (!_mqttClient->connect(_clientName)) {
      Serial.print("failed, rc=");
      Serial.print(_mqttClient->state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
  _mqttClient->subscribe("/foo/bar/from/lib");
}
