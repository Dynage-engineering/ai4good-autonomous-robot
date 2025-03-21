#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// Pin declarations for each component
#define DC_MOTOR_PIN1 9
#define DC_MOTOR_PIN2 8
#define DC_MOTOR_ENABLE 7

#define ULTRASONIC_TRIGGER_PIN 5
#define ULTRASONIC_ECHO_PIN 6

#define COLOR_SENSOR_S0 7
#define COLOR_SENSOR_S1 8
#define COLOR_SENSOR_S2 9
#define COLOR_SENSOR_S3 10
#define COLOR_SENSOR_OUT 11

#define GRIPPER_PICKER 12
#define GRIPPER_ELBOW 13
#define GRIPPER_SHOULDER 14
#define GRIPPER_WAIST 15

#define STEERING_SERVO_PIN 16

void initializePins();

#endif