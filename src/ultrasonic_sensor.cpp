#include <Arduino.h>
#include "autonomous_robot/ultrasonic_sensor.h"
# include "pin_config.h"

UltrasonicSensor::UltrasonicSensor(int triggerPin = ULTRASONIC_TRIGGER_PIN , int echoPin = ULTRASONIC_ECHO_PIN)
    : triggerPin_(triggerPin), echoPin_(echoPin) {
}

float UltrasonicSensor::getDistance() {
    digitalWrite(triggerPin_, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin_, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin_, LOW);

    long duration = pulseIn(echoPin_, HIGH);
    return duration * 0.034 / 2;  // Convert to distance in cm
}