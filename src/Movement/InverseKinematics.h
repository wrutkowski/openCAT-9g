#ifndef InverseKinematics_h
#define InverseKinematics_h

#include <math.h>
#include "Leg.h"

struct InverseKinematicsModel {
    float shoulderPivotSides;
    float shoulderPivot;
    float knee;
};

class InverseKinematics {

public:
    InverseKinematics(float femurLength_, float tibiaLength_) :
        femurLength(femurLength_),
        tibiaLength(tibiaLength_) {};
    InverseKinematicsModel model(LEG leg, float x, float y, float z, float yaw, float pitch, float roll);

private:
    float femurLength;
    float tibiaLength;
};

#endif
