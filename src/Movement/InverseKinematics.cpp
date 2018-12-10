#include "InverseKinematics.h"

InverseKinematicsModel InverseKinematics::model(LEG leg, float x, float y, float z, float yaw, float pitch, float roll) {

    InverseKinematicsModel model;

    float L = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

    model.knee = acos((pow(femurLength, 2) + pow(tibiaLength, 2) - pow(L, 2)) / (2 * femurLength * tibiaLength));

    float shoulderPivot1 = acos((pow(L, 2) + pow(femurLength, 2) - pow(tibiaLength, 2)) / (2 * L * femurLength));
    float shoulderPivot2 = -atan2(x, z);
    model.shoulderPivot = shoulderPivot1 + shoulderPivot2;

    model.shoulderPivotSides = atan2(y, L);

    return model;
}
