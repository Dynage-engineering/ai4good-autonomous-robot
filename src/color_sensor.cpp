#include <Arduino.h>
#include "autonomous_robot/color_sensor.h"
#include "pin_config.h"

ColorSensor::ColorSensor(int s0 = COLOR_SENSOR_S0, int s1 = COLOR_SENSOR_S1, int s2 = COLOR_SENSOR_S2, int s3 = COLOR_SENSOR_S3 ,int out = COLOR_SENSOR_OUT)
    : s0_(s0), s1_(s1), s2_(s2), s3_(s3), out_(out) {
    digitalWrite(s0_, HIGH);
    digitalWrite(s1_, LOW);
}

String ColorSensor::getColor() {
    // Implement color detection logic
    // Red, Blue, Green, Yellow, White, Black
    return "Red";
}