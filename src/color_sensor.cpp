#include <Arduino.h>
#include "autonomous_robot/color_sensor.h"

ColorSensor::ColorSensor(int s0, int s1, int s2, int s3, int out)
    : s0_(s0), s1_(s1), s2_(s2), s3_(s3), out_(out) {
    pinMode(s0_, OUTPUT);
    pinMode(s1_, OUTPUT);
    pinMode(s2_, OUTPUT);
    pinMode(s3_, OUTPUT);
    pinMode(out_, INPUT);
    digitalWrite(s0_, HIGH);
    digitalWrite(s1_, LOW);
}

String ColorSensor::getColor() {
    // Implement color detection logic
    // Red, Blue, Green, Yellow, White, Black
    return "Red";
}