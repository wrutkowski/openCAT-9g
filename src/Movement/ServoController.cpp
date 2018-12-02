#include "ServoController.h"

void ServoController::setAngle(uint8_t servoNumber, float angle) {
    
    // TODO Big swtich statement matching all servos with their pulse characteristcs.
    int pulse = 300;
    pwm.setPWM(servoNumber, 0, pulse);
}
