#include "Networking/Networking.h"
#include "Movement/Movement.h"

const char* APssid = "openCAT-9g";
const char* APpassword = "catnip";
const char* ssid = "";
const char* password = "";
const char* host = "opencat";

Networking networking(80, 81);
Movement movement;

void onReceivedText(uint8_t *payload);

void setup() {

    Serial.begin(115200);

    networking.setup_ap(APssid, APpassword, ssid, password);
    networking.setup_dns(host);
    networking.setup_webSocket(onReceivedText);
}

void loop() {

    networking.loop();
}

void onReceivedText(uint8_t *payload) {

    // uint32_t commandData = (uint32_t) strtol((const char *) &payload[0], NULL, 16);   // decode command data
    // int servoNumber = (commandData >> 16) & 0b1111;
    // int pulse = commandData & 4095;
    // Serial.printf("Command (%s -> %d): NUM=%d, PULSE=%d\n", payload, commandData, servoNumber, pulse);

    movement.standUp();
}
