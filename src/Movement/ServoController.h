#ifndef ServoController_h
#define ServoController_h

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

class ServoController {

public:
    ServoController() {
        pwm.begin();
        pwm.setPWMFreq(60);
    };
    void setAngle(uint8_t servoNumber, float angle);

private:
    Adafruit_PWMServoDriver pwm;
};

#endif
