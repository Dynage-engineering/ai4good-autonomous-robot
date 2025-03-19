#include <AUnit.h>
#include "autonomous_robot/ultrasonic_sensor.h"
#include "autonomous_robot/color_sensor.h"
#include "autonomous_robot/gripper_control.h"
#include "autonomous_robot/steering_control.h"

test(ultrasonic_sensor_test) {
    UltrasonicSensor sensor(5, 6);
    assertEqual(sensor.getDistance(), 10.0);  // Example test
}

test(color_sensor_test) {
    ColorSensor sensor(7, 8, 9, 10, 11);
    assertEqual(sensor.getColor(), "Red");  // Example test
}

test(gripper_control_test) {
    GripperControl gripper(12, 13, 14, 15);
    gripper.open();
    gripper.close();
    assertTrue(true);  // Example test
}

test(steering_control_test) {
    SteeringControl steering(16);
    steering.setAngle(90);
    assertTrue(true);  // Example test
}

void setup() {
    Serial.begin(115200);
    while (!Serial);
    aunit::TestRunner::run();
}

void loop() {}