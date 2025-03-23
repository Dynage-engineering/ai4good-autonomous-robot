#include "pin_config.h"
#include <L298N.h>

// Pin definition
const unsigned int IN1 = DC_MOTOR_PIN1;
const unsigned int IN2 = DC_MOTOR_PIN2;
const unsigned int EN = DC_MOTOR_ENABLE;

// Create one motor instance
L298N motor(EN, IN1, IN2);