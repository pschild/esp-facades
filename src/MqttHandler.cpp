#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "MqttHandler.h"
#include <map>

MqttHandler::MqttHandler(char* brokerIP, String clientName) {
  _brokerIP = brokerIP;
  _clientName = clientName;
  _wifiClient = new WiFiClient();
}

void MqttHandler::setup() {
  if (_wifiClient->status() != WL_CONNECTED) {
    _mqttClient = new PubSubClient(*_wifiClient);
    _mqttClient->setServer(_brokerIP, 1883);
    _mqttClient->setCallback(MqttHandler::callback);
  } else {
    throw "Error: Cannot connect to PubSubClient as Wifi is not connected!";
  }
}

void MqttHandler::loop() {
  if (!_mqttClient->connected()) {
    reconnect();
  }

  _mqttClient->loop();
}

void MqttHandler::reconnect() {
  while (!_mqttClient->connected()) {
    Serial.println("Reconnecting...");

    char clientName[_clientName.length() + 1];
    strcpy(clientName, _clientName.c_str());
    if (!_mqttClient->connect(clientName)) {
      Serial.print("failed, rc=");
      Serial.print(_mqttClient->state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
  if (_connectedCallback) {
    _connectedCallback();
  }
}

void MqttHandler::callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received message [");
  Serial.print(topic);
  Serial.print("] ");
  char msg[length+1];
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    msg[i] = (char)payload[i];
  }
  Serial.println();

  msg[length] = '\0';
  Serial.println(msg);
  
  if (_callbackMap[topic]) {
    _callbackMap[topic](msg);
  }

}

void MqttHandler::setOnConnectedCallback(std::function<void()> callback) {
  _connectedCallback = callback;
}

boolean MqttHandler::subscribe(const char* topic, std::function<void(char* payload)> cbFunc) {
  _callbackMap[topic] = cbFunc;
  return _mqttClient->subscribe(topic);
}

boolean MqttHandler::unsubscribe(const char* topic) {
  _callbackMap.erase(topic);
  return _mqttClient->unsubscribe(topic);
}

// You must add a definition after class, see https://stackoverflow.com/a/14331502/5276055
std::map<std::string, std::function<void(char* payload)>> MqttHandler::_callbackMap;
