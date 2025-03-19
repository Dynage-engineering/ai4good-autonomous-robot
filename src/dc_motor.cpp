#include "autonomous_robot/dc_motor.h"
#include <Arduino.h>

DCMotor::DCMotor(int enablePin, int in1Pin, int in2Pin)
    : enablePin_(enablePin), in1Pin_(in1Pin), in2Pin_(in2Pin) {
    pinMode(enablePin_, OUTPUT);
    pinMode(in1Pin_, OUTPUT);
    pinMode(in2Pin_, OUTPUT);
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