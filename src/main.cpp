#include <Arduino.h>
#include "autonomous_robot/dc_motor.h"
#include "autonomous_robot/ultrasonic_sensor.h"
#include "autonomous_robot/color_sensor.h"
#include "autonomous_robot/gripper_control.h"
#include "autonomous_robot/steering_control.h"
#include "pin_config.h"

// Instantiate components
DCMotor rearMotor(DC_MOTOR_ENABLE, DC_MOTOR_PIN1, DC_MOTOR_PIN2);
UltrasonicSensor ultrasonicSensor(ULTRASONIC_TRIGGER_PIN, ULTRASONIC_ECHO_PIN);
ColorSensor colorSensor(COLOR_SENSOR_S0, COLOR_SENSOR_S1, COLOR_SENSOR_S2, COLOR_SENSOR_S3, COLOR_SENSOR_OUT);
GripperControl gripper(GRIPPER_SERVO_PIN1, GRIPPER_SERVO_PIN2, GRIPPER_SERVO_PIN3, GRIPPER_SERVO_PIN4);
SteeringControl steering(STEERING_SERVO_PIN);

void setup() {
    Serial.begin(115200);
    initializePins();  // Initialize all pins

    // Ensure components are in a safe state
    rearMotor.stop();
    gripper.close();
    steering.setAngle(90);  // Set steering to neutral position
}

void loop() {
    // Move to the middle of the arena
    rearMotor.forward(255);  // Move forward at full speed
    delay(2000);             // Adjust delay based on distance to middle
    rearMotor.stop();        // Stop the motor

    // Collect 6 red blocks
    for (int i = 0; i < 6; i++) {
        if (ultrasonicSensor.getDistance() < 20) {  // If block is within 20cm
            gripper.open();                        // Open the gripper
            delay(500);                            // Wait for gripper to open
            gripper.close();                       // Close the gripper to grip the block
            delay(500);                            // Wait for gripper to close
            rearMotor.backward(255);               // Move back to Hospital
            delay(1000);                           // Adjust delay based on distance
            rearMotor.stop();                      // Stop the motor
            gripper.open();                        // Release the block
            delay(500);                            // Wait for gripper to open
            rearMotor.forward(255);                // Return to middle
            delay(1000);                           // Adjust delay based on distance
            rearMotor.stop();                      // Stop the motor
        }
    }

    // Move to the start arena
    steering.setAngle(180);  // Turn left (adjust angle as needed)
    delay(500);              // Wait for the turn to complete
    rearMotor.forward(255);  // Move forward
    delay(1000);             // Adjust delay based on distance
    rearMotor.stop();        // Stop the motor

    // Collect 4 green blocks
    for (int i = 0; i < 4; i++) {
        if (colorSensor.getColor() == "Green") {   // If block is green
            gripper.open();                        // Open the gripper
            delay(500);                            // Wait for gripper to open
            gripper.close();                       // Close the gripper to grip the block
            delay(500);                            // Wait for gripper to close
            rearMotor.backward(255);               // Move back to Refuge
            delay(1000);                           // Adjust delay based on distance
            rearMotor.stop();                      // Stop the motor
            gripper.open();                        // Release the block
            delay(500);                            // Wait for gripper to open
            rearMotor.forward(255);                // Return to start arena
            delay(1000);                           // Adjust delay based on distance
            rearMotor.stop();                      // Stop the motor
        }
    }

    // End of mission
    rearMotor.stop();
    while (true);  // Stop the robot
}