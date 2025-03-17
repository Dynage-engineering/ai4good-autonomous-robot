#include <gtest/gtest.h>
#include "autonomous_robot/ultrasonic_sensor.hpp"

TEST(TestUltrasonicSensor, TestDistanceMeasurement) {
    UltrasonicSensor sensor;
    sensor.setDistance(10.0f);
    EXPECT_FLOAT_EQ(sensor.getDistance(), 10.0f);
}
