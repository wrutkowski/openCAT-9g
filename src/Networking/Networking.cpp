#include "Networking.h"

void Networking::setup_ap(const char *APssid, const char *APpassword, const char *ssid, const char *password) {

    WiFi.softAP(APssid, APpassword);             // Start the access point
    Serial.print("Access Point \"");
    Serial.print(APssid);
    Serial.println("\" started\r\n");

    wifiMulti.addAP(ssid, password);

    Serial.print("Connecting");
    while (wifiMulti.run() != WL_CONNECTED && WiFi.softAPgetStationNum() < 1) {  // Wait for the Wi-Fi to connect
        digitalWrite(LED, LOW); delay(100);
        digitalWrite(LED, HIGH); delay(400);
        Serial.print('.');
    }
    Serial.println();

    if (WiFi.softAPgetStationNum() == 0) {      // If the ESP is connected to an AP
        Serial.print("Connected to ");
        Serial.println(WiFi.SSID());             // Tell us what network we're connected to
        Serial.print("IP address: ");
        Serial.print(WiFi.localIP());            // Send the IP address of the ESP8266 to the computer
    } else {                                   // If a station is connected to the ESP SoftAP
        Serial.print("Station connected to openCAT-9g AP");
    }
    Serial.println();

    digitalWrite(LED, LOW); delay(100);
    digitalWrite(LED, HIGH); delay(100);
    digitalWrite(LED, LOW); delay(100);
    digitalWrite(LED, HIGH); delay(100);
    digitalWrite(LED, LOW); delay(100);
    digitalWrite(LED, HIGH);
}

void Networking::setup_dns(const char *host) {

    MDNS.begin(host);
    Serial.print("mDNS responder started: http://");
    Serial.print(host);
    Serial.println(".local");
}

void Networking::setup_webSocket(WebSocketReceivedTextEvent onReceivedText) {

    onWebSocketReceivedText = onReceivedText;

    webSocket.begin();
    webSocket.onEvent(std::bind(&Networking::webSocketEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    Serial.println("WebSocket server started.");

}

void Networking::loop() {
    
    webSocket.loop();
    webServer.handleClient();
}

void Networking::webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            break;

        case WStype_CONNECTED:
            {
                IPAddress ip = webSocket.remoteIP(num);
                Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

                // send message to client
                webSocket.sendTXT(num, "Connected");
            }
            break;

        case WStype_TEXT: {
            Serial.printf("[%u] get Text: %s\n", num, payload);

            onWebSocketReceivedText(payload);

            break;
        }
    }
}
