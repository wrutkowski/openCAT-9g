#include "Movement.h"

void Movement::standUp() {

    setLeg(FRONT_LEFT, 0, 0, 70, 0, 0, 0);
    setLeg(FRONT_RIGHT, 0, 0, 70, 0, 0, 0);
    setLeg(REAR_LEFT, 0, 0, 70, 0, 0, 0);
    setLeg(REAR_RIGHT, 0, 0, 70, 0, 0, 0);
}

void Movement::layDown() {

    // TODO
}

void Movement::setLeg(LEG leg, float x, float y, float z, float yaw, float pitch, float roll) {

    Serial.printf("setLeg: %d => x: %f, y: %f, z: %f\n", leg, x, y, z);

    InverseKinematicsModel ik = inverseKinematics.model(leg, x, y, z, yaw, pitch, roll);

    // unreachable position
    if (isnan(ik.shoulderPivotSides) || isnan(ik.shoulderPivot) || isnan(ik.knee)) {
        Serial.println("Incorrect position");
        return;
    }

    // meachnical constrains
    if (ik.shoulderPivotSides < 17.5 || ik.shoulderPivotSides > 17.5) {
        Serial.println("Incorrect position: meachnical constrains");
        return;
    }
    if (ik.shoulderPivot < 43.5 || ik.shoulderPivot > 130) {
        Serial.println("Incorrect position: meachnical constrains");
        return;
    }
    if (ik.knee < 17 || ik.knee > 160) {
        Serial.println("Incorrect position: meachnical constrains");
        return;
    }

    uint8_t legNumber = legNumberFor(leg);
    uint8_t hipServoSubIndex, kneeServoSubIndex, ankleServoSubIndex;
    switch (leg) {
        case FRONT_LEFT:
            hipServoSubIndex = 2;
            kneeServoSubIndex = 1;
            ankleServoSubIndex = 0;

            ik.shoulderPivotSides *= -1;

            break;
        case FRONT_RIGHT:
            hipServoSubIndex = 1;
            kneeServoSubIndex = 0;
            ankleServoSubIndex = 2;
            break;
        case REAR_LEFT:
            hipServoSubIndex = 1;
            kneeServoSubIndex = 2;
            ankleServoSubIndex = 0;

            ik.shoulderPivotSides *= -1;

            break;
        case REAR_RIGHT:
            hipServoSubIndex = 1;
            kneeServoSubIndex = 0;
            ankleServoSubIndex = 2;
            break;
    }
    servoController.setAngle(legNumber * 4 + hipServoSubIndex, ik.shoulderPivotSides);
    servoController.setAngle(legNumber * 4 + kneeServoSubIndex, ik.shoulderPivot);
    servoController.setAngle(legNumber * 4 + ankleServoSubIndex, ik.knee);
}

uint8_t Movement::legNumberFor(LEG leg) {

    switch (leg) {
        case FRONT_LEFT: return 1;
        case FRONT_RIGHT: return 2;
        case REAR_LEFT: return 3;
        case REAR_RIGHT: return 0;
    }
}
