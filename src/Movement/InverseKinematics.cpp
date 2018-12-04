#include "InverseKinematics.h"

InverseKinematicsModel InverseKinematics::model(LEG leg, float x, float y, float z_, float yaw, float pitch, float roll) {

    InverseKinematicsModel model;

    float z = -z_;
    float L = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

    model.knee = acos((pow(femurLength, 2) + pow(tibiaLength, 2) - pow(L, 2)) / (2 * femurLength * tibiaLength));

    float knee1 = acos((pow(L, 2) + pow(femurLength, 2) - pow(tibiaLength, 2)) / (2 * L * femurLength));
    float knee2 = acos((pow(L, 2) + pow(z, 2) - pow(x, 2)) / (2 * L * z) );
    model.shoulderPivot = knee1 + knee2;

    model.shoulderPivotSides = atan2(y, L);

    return model;
}
