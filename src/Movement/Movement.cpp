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

    // Serial.printf("setLeg: %d => x: %f, y: %f, z: %f\n", leg, x, y, z);

    InverseKinematicsModel ik = inverseKinematics.model(leg, x, y, z, yaw, pitch, roll);

    // Serial.printf("ik => shoulderPivotSides: %f, shoulderPivot: %f, knee: %f\n", ik.shoulderPivotSides, ik.shoulderPivot, ik.knee);

    // unreachable position
    if (isnan(ik.shoulderPivotSides) || isnan(ik.shoulderPivot) || isnan(ik.knee)) {
        Serial.println("Incorrect position");
        return;
    }

    // adjust angles for servo mount setting
    if (x >= 0) {
        ik.shoulderPivot += 2 * M_PI;
    }
    ik.shoulderPivot -= 0.7 * M_PI;

    InverseKinematicsModel ikDegrees = InverseKinematicsModel{ik.shoulderPivotSides * 180.0 / M_PI, ik.shoulderPivot * 180.0 / M_PI, ik.knee * 180.0 / M_PI};

    // Serial.printf("ikDegrees => shoulderPivotSides: %f, shoulderPivot: %f, knee: %f\n", ikDegrees.shoulderPivotSides, ikDegrees.shoulderPivot, ikDegrees.knee);

    // meachnical constrains
    if (ikDegrees.shoulderPivotSides < -17.5 || ikDegrees.shoulderPivotSides > 17.5) {
        Serial.printf("Incorrect position: meachnical constrains on shoulderPivotSides. Requested %f, for allowed range <%f, %f>\n", ikDegrees.shoulderPivotSides, -17.5, 17.5);
        return;
    }
    if (ikDegrees.shoulderPivot < 43.5 || ikDegrees.shoulderPivot > 130) {
        Serial.printf("Incorrect position: meachnical constrains on shoulderPivot. Requested %f, for allowed range <%f, %f>\n", ikDegrees.shoulderPivot, 43.5, 130.0);
        return;
    }
    if (ikDegrees.knee < 17 || ikDegrees.knee > 160) {
        Serial.printf("Incorrect position: meachnical constrains on knee. Requested %f, for allowed range <%f, %f>\n", ikDegrees.knee, 17.0, 160.0);
        return;
    }

    uint8_t legNumber = legNumberFor(leg);
    uint8_t shoulderPivotSidesServoSubIndex = 0, shoulderPivotServoSubIndex = 0, kneeServoSubIndex = 0;
    switch (leg) {
        case FRONT_LEFT:
            shoulderPivotSidesServoSubIndex = 2;
            shoulderPivotServoSubIndex = 1;
            kneeServoSubIndex = 0;
            break;
        case FRONT_RIGHT:
            shoulderPivotSidesServoSubIndex = 1;
            shoulderPivotServoSubIndex = 0;
            kneeServoSubIndex = 2;
            break;
        case REAR_LEFT:
            shoulderPivotSidesServoSubIndex = 1;
            shoulderPivotServoSubIndex = 2;
            kneeServoSubIndex = 0;
            break;
        case REAR_RIGHT:
            shoulderPivotSidesServoSubIndex = 1;
            shoulderPivotServoSubIndex = 0;
            kneeServoSubIndex = 2;
            break;
    }
    servoController.setAngle(legNumber * 4 + shoulderPivotSidesServoSubIndex, ik.shoulderPivotSides);
    servoController.setAngle(legNumber * 4 + shoulderPivotServoSubIndex, ik.shoulderPivot);
    servoController.setAngle(legNumber * 4 + kneeServoSubIndex, ik.knee);
}

uint8_t Movement::legNumberFor(LEG leg) {

    switch (leg) {
        case FRONT_LEFT: return 1;
        case FRONT_RIGHT: return 2;
        case REAR_LEFT: return 3;
        case REAR_RIGHT: return 0;
    }
}
