#include "autonomous_robot/ultrasonic_sensor.hpp"

UltrasonicSensor::UltrasonicSensor() : distance_(0.0f) {}

void UltrasonicSensor::setDistance(float distance) {
    distance_ = distance;
}

float UltrasonicSensor::getDistance() {
    return distance_;
}
