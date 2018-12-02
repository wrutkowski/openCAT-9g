#ifndef InverseKinematics_h
#define InverseKinematics_h

#include <Arduino.h>
#include "Leg.h"

struct InverseKinematicsModel {
    float hip;
    float knee;
    float ankle;
};

class InverseKinematics {

public:
    InverseKinematicsModel model(LEG leg, float x, float y, float z, float yaw, float pitch, float roll);

};

#endif
