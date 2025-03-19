#include "autonomous_robot/steering_control.h"

SteeringControl::SteeringControl(int pin) {
    servo_.attach(pin);
}

void SteeringControl::setAngle(int angle) {
    servo_.write(angle);
}