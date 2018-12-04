#ifndef Movement_h
#define Movement_h

#include <Arduino.h>
#include "InverseKinematics.h"
#include "ServoController.h"
#include "Leg.h"

class Movement {

public:
    Movement (float femurLength, float tibiaLength) :
        inverseKinematics(femurLength, tibiaLength) {};
    void standUp();
    void layDown();
    void setLeg(LEG leg, float x, float y, float z, float yaw, float pitch, float roll);

private:
    InverseKinematics inverseKinematics;
    ServoController servoController;

    uint8_t legNumberFor(LEG leg);
};

#endif
