#ifndef MqttHandler_h
#define MqttHandler_h

#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

class MqttHandler {
  public:
    MqttHandler(char* brokerIP, const String clientName);
    void setup();
    void loop();
    void reconnect();
    void setOnConnectedCallback(std::function<void()> callback);
    void setOnMessageCallback(std::function<void(char* topic, char* message)> callback);
    boolean subscribe(const char* topic);
    boolean unsubscribe(const char* topic);
    boolean publish(const char* topic, const char* payload);
  private:
    char* _brokerIP;
    String _clientName;
    WiFiClient* _wifiClient;
    PubSubClient* _mqttClient;
    std::function<void()> _connectedCallback;
};

#endif
