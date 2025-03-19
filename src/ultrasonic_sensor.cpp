#include <Arduino.h>
#include "autonomous_robot/ultrasonic_sensor.h"

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin)
    : triggerPin_(triggerPin), echoPin_(echoPin) {
    pinMode(triggerPin_, OUTPUT);
    pinMode(echoPin_, INPUT);
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