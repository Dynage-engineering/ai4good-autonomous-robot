#include "pin_config.h"
#include <Arduino.h>

void initializePins() {
    // DC Motor pins
    pinMode(DC_MOTOR_PIN1, OUTPUT);
    pinMode(DC_MOTOR_PIN2, OUTPUT);
    pinMode(DC_MOTOR_ENABLE, OUTPUT);

    // Ultrasonic sensor pins
    pinMode(ULTRASONIC_TRIGGER_PIN, OUTPUT);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);

    // Color sensor pins
    pinMode(COLOR_SENSOR_S0, OUTPUT);
    pinMode(COLOR_SENSOR_S1, OUTPUT);
    pinMode(COLOR_SENSOR_S2, OUTPUT);
    pinMode(COLOR_SENSOR_S3, OUTPUT);
    pinMode(COLOR_SENSOR_OUT, INPUT);

    // Gripper servo pins
    pinMode(GRIPPER_SERVO_PIN1, OUTPUT);
    pinMode(GRIPPER_SERVO_PIN2, OUTPUT);
    pinMode(GRIPPER_SERVO_PIN3, OUTPUT);
    pinMode(GRIPPER_SERVO_PIN4, OUTPUT);

    // Steering servo pin
    pinMode(STEERING_SERVO_PIN, OUTPUT);
}