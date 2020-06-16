#ifndef MqttHandler_h
#define MqttHandler_h

#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <map>

class MqttHandler {
  public:
    MqttHandler(char* brokerIP, String clientName);
    void setup();
    void loop();
    void reconnect();
    static void callback(char* topic, byte* payload, unsigned int length);
    void setOnConnectedCallback(std::function<void()> callback);
    boolean subscribe(const char* topic, std::function<void(char* payload)> cb);
    boolean unsubscribe(const char* topic);
  private:
    char* _brokerIP;
    String _clientName;
    WiFiClient* _wifiClient;
    PubSubClient* _mqttClient;
    std::function<void()> _connectedCallback;
    static std::map<std::string, std::function<void(char* payload)>> _callbackMap;
};

#endif
