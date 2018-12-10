#include "Config.h"
#include "Networking/Networking.h"
#include "Movement/Movement.h"

#define FEMUR_LENGTH 48.1
#define TIBIA_LENGTH 51

Networking networking(80, 81);
Movement movement(FEMUR_LENGTH, TIBIA_LENGTH);

int x, y, z;

void onReceivedText(uint8_t *payload);

void setup() {

    Serial.begin(115200);

    networking.setup_ap(APssid, APpassword, ssid, password);
    networking.setup_dns(host);
    networking.setup_webSocket(onReceivedText);

    movement.setLeg(FRONT_LEFT, 0, 0, -40, 0, 0, 0);
    movement.setLeg(FRONT_RIGHT, 0, 0, -40, 0, 0, 0);
    movement.setLeg(REAR_LEFT, 0, 0, -40, 0, 0, 0);
    movement.setLeg(REAR_RIGHT, 0, 0, -40, 0, 0, 0);
}

void loop() {

    networking.loop();
}

void onReceivedText(uint8_t *payload) {

    uint32_t commandData = (uint32_t) strtol((const char *) &payload[0], NULL, 16);   // decode command data
    int id = (commandData >> 16) & 3;
    int value = (commandData & 255) - 128;
    // int pulse = commandData & 4095;
    // Serial.printf("Command (%s -> %d): NUM=%d, PULSE=%d\n", payload, commandData, servoNumber, pulse);
    switch (id) {
    case 0:
        x = value;
        break;
    case 1:
        y = value;
        break;
    case 2:
        z = value;
        break;
    }

    movement.setLeg(FRONT_LEFT, x, y, z, 0, 0, 0);
    movement.setLeg(FRONT_RIGHT, x, y, z, 0, 0, 0);
    movement.setLeg(REAR_LEFT, x, y, z, 0, 0, 0);
    movement.setLeg(REAR_RIGHT, x, y, z, 0, 0, 0);
}
