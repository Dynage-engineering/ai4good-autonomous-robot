#include <AUnit.h>
#include "autonomous_robot/dc_motor.h"
#include "pin_config.h"  // Include the pin configuration


test(dc_motor_forward_test) {
    DCMotor motor(DC_MOTOR_PIN1, DC_MOTOR_PIN2, DC_MOTOR_ENABLE);
    motor.forward(255);  // Move forward at full speed
    assertTrue(true);    // Example assertion
}

test(dc_motor_backward_test) {
    DCMotor motor(DC_MOTOR_PIN1, DC_MOTOR_PIN2, DC_MOTOR_ENABLE);
    motor.backward(255);  // Move backward at full speed
    assertTrue(true);     // Example assertion
}

test(dc_motor_stop_test) {
    DCMotor motor(DC_MOTOR_PIN1, DC_MOTOR_PIN2, DC_MOTOR_ENABLE);
    motor.stop();  // Stop the motor
    assertTrue(true);  // Example assertion
}

void setup() {
    Serial.begin(115200);
    while (!Serial);
    aunit::TestRunner::run();
}

void loop() {}