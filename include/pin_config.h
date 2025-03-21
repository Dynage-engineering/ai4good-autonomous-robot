#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// Pin declarations for each component
#define DC_MOTOR_PIN1 22
#define DC_MOTOR_PIN2 23
#define DC_MOTOR_ENABLE 21

#define ULTRASONIC_TRIGGER_PIN 13
#define ULTRASONIC_ECHO_PIN 6

#define COLOR_SENSOR_S0 18
#define COLOR_SENSOR_S1 5
#define COLOR_SENSOR_S2 17
#define COLOR_SENSOR_S3 4
#define COLOR_SENSOR_OUT 16

#define GRIPPER_PICKER 26
#define GRIPPER_ELBOW 25
#define GRIPPER_SHOULDER 33
#define GRIPPER_WAIST 32

#define STEERING_SERVO_PIN 27

void initializePins();

#endif