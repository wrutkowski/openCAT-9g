#include "ServoController.h"

void ServoController::setAngle(uint8_t servoNumber, float angle) {

    // TODO Big switch statement matching all servos with their pulse characteristcs and mechanical limits.
    angle = angle * 180.0 / M_PI;
    uint16_t pulse;
    switch (servoNumber) {
        // REAR RIGHT
        case 0: pulse = constrain(map(angle, 43.5, 130, 440, 600), 440, 600); break; // shoulderPivot
        case 1: pulse = constrain(map(angle, -17.5, 17.5, 380, 450), 380, 450); break; // shoulderPivotSides
        case 2: pulse = constrain(map(angle, 17, 160, 200, 550), 200, 550); break; // knee

        // FRONT LEFT
        case 4: pulse = constrain(map(angle, 17, 160, 215, 540), 215, 540); break; // knee
        case 5: pulse = constrain(map(angle, 43.5, 130, 355, 570), 355, 570); break; // shoulderPivot
        case 6: pulse = constrain(map(angle, -17.5, 17.5, 355, 435), 355, 435); break; // shoulderPivotSides

        // FRONT RIGHT
        case 8: pulse = constrain(map(angle, 43.5, 130, 360, 570), 360, 570); break; // shoulderPivot
        case 9: pulse = constrain(map(angle, -17.5, 17.5, 310, 385), 310, 385); break; // shoulderPivotSides
        case 10: pulse = constrain(map(angle, 17, 160, 175, 500), 175, 500); break; // knee

        // REAR LEFT
        case 12: pulse = constrain(map(angle, 17, 160, 170, 510), 170, 510); break; // knee
        case 13: pulse = constrain(map(angle, -17.5, 17.5, 225, 285), 225, 285); break; // shoulderPivotSides
        case 14: pulse = constrain(map(angle, 43.5, 130, 350, 550), 350, 550); break; // shoulderPivot
    }
    Serial.printf("Servo %d: angle (%f) -> pulse (%d)\n", servoNumber, angle, pulse);
    pwm.setPWM(servoNumber, 0, pulse);
}
