#include "ServoController.h"

void ServoController::setAngle(uint8_t servoNumber, float angle) {

    angle = angle * 180.0 / M_PI;
    uint16_t pulse = 0;
    switch (servoNumber) {
        // REAR RIGHT
        case 0: pulse = constrain(map(angle, 130, 43.5, 440, 600), 440, 600); break; // shoulderPivot
        case 1: pulse = constrain(map(angle, -17.5, 17.5, 380, 450), 380, 450); break; // shoulderPivotSides
        case 2: pulse = constrain(map(angle, 17, 160, 200, 550), 200, 550); break; // knee

        // FRONT LEFT
        case 4: pulse = constrain(map(angle, 160, 17, 215, 540), 215, 540); break; // knee
        case 5: pulse = constrain(map(angle, 43.5, 130, 355, 590), 355, 570); break; // shoulderPivot
        case 6: pulse = constrain(map(angle, -17.5, 17.5, 355, 435), 355, 435); break; // shoulderPivotSides

        // FRONT RIGHT
        case 8: pulse = constrain(map(angle + 5, 130, 43.5, 380, 570), 360, 570); break; // shoulderPivot
        case 9: pulse = constrain(map(angle, -17.5, 17.5, 310, 385), 310, 385); break; // shoulderPivotSides
        case 10: pulse = constrain(map(angle + 10, 17, 160, 175, 500), 175, 500); break; // knee

        // REAR LEFT
        case 12: pulse = constrain(map(angle + 10, 160, 17, 170, 520), 170, 520); break; // knee
        case 13: pulse = constrain(map(angle, -17.5, 17.5, 225, 285), 225, 285); break; // shoulderPivotSides
        case 14: pulse = constrain(map(angle + 13, 43.5, 130, 350, 550), 350, 550); break; // shoulderPivot
    }
    // Serial.printf("Servo %d: angle (%f) -> pulse (%d)\n", servoNumber, angle, pulse);
    pwm.setPWM(servoNumber, 0, pulse);
}
