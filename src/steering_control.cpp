#include "autonomous_robot/steering_control.h"
#include <pin_config.h>

SteeringControl::SteeringControl(int pin = STEERING_SERVO_PIN) {
    servo_.attach(pin);
}

void SteeringControl::setAngle(int angle) {
    servo_.write(angle);
}