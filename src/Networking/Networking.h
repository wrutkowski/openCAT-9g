#ifndef Networking_h
#define Networking_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WebSocketsServer.h>

#define LED D4

typedef void (*WebSocketReceivedTextEvent)(uint8_t *payload);

class Networking {

public:
    Networking(uint16_t webServerPort, uint16_t webSocketPort) :
        webServer(webServerPort),
        webSocket(webSocketPort) {};
    void setup_ap(const char *APssid, const char *APpassword, const char *ssid, const char *password);
    void setup_dns(const char *host);
    void setup_webSocket(WebSocketReceivedTextEvent onReceivedText);
    void loop();
    
private:
    ESP8266WiFiMulti wifiMulti;
    ESP8266WebServer webServer;
    WebSocketsServer webSocket;
    WebSocketReceivedTextEvent onWebSocketReceivedText;

    void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
};

#endif
