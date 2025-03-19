#include "autonomous_robot/dc_motor.h"
#include <Arduino.h>
#include "pin_config.h" 


DCMotor::DCMotor(int enablePin = DC_MOTOR_ENABLE, int in1Pin = DC_MOTOR_PIN1, int in2Pin = DC_MOTOR_PIN2)
    : enablePin_(enablePin), in1Pin_(in1Pin), in2Pin_(in2Pin) {
    stop();  // Initialize motor in stopped state
}

void DCMotor::forward(int speed) {
    analogWrite(enablePin_, speed);
    digitalWrite(in1Pin_, HIGH);
    digitalWrite(in2Pin_, LOW);
}

void DCMotor::backward(int speed) {
    analogWrite(enablePin_, speed);
    digitalWrite(in1Pin_, LOW);
    digitalWrite(in2Pin_, HIGH);
}

void DCMotor::stop() {
    digitalWrite(in1Pin_, LOW);
    digitalWrite(in2Pin_, LOW);
    analogWrite(enablePin_, 0);
}