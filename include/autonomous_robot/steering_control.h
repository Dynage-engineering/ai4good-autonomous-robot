#ifndef AUTONOMOUS_ROBOT_STEERING_CONTROL_H
#define AUTONOMOUS_ROBOT_STEERING_CONTROL_H

#include <ESP32Servo.h>

class SteeringControl {
public:
    SteeringControl(int pin);
    void setAngle(int angle);

private:
    Servo servo_;
};

#endif