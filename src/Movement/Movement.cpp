#include "Movement.h"

void Movement::standUp() {

    // TODO
}

void Movement::layDown() {

    // TODO
}

void Movement::setLeg(LEG leg, float x, float y, float z, float yaw, float pitch, float roll) {

    InverseKinematicsModel ik = inverseKinematics.model(leg, x, y, z, yaw, pitch, roll);

    uint8_t legNumber = legNumberFor(leg);
    servoController.setAngle(legNumber * 4, ik.hip);
    servoController.setAngle(legNumber * 4 + 1, ik.knee);
    servoController.setAngle(legNumber * 4 + 2, ik.ankle);
}

uint8_t Movement::legNumberFor(LEG leg) {

    switch (leg) {
        case FRONT_LEFT: return 1;
        case FRONT_RIGHT: return 2;
        case REAR_LEFT: return 3;
        case REAR_RIGHT: return 0;
    }

    return -1;
}
