#include <Arduino.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/string.h>
#include <micro_ros_platformio.h>  // Include Micro-ROS transport header
#include "autonomous_robot/dc_motor.h"
#include "autonomous_robot/ultrasonic_sensor.h"
#include "autonomous_robot/color_sensor.h"
#include "autonomous_robot/gripper_control.h"
#include "autonomous_robot/steering_control.h"
#include "pin_config.h"


// Micro-ROS objects
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;

// Publishers and subscribers
rcl_publisher_t distance_publisher;
rcl_publisher_t color_publisher;
rcl_subscription_t command_subscriber;

// Messages
std_msgs__msg__Int32 distance_msg;
std_msgs__msg__String color_msg;
std_msgs__msg__String command_msg;

// Instantiate components
DCMotor rearMotor(DC_MOTOR_ENABLE, DC_MOTOR_PIN1, DC_MOTOR_PIN2);
UltrasonicSensor ultrasonicSensor(ULTRASONIC_TRIGGER_PIN, ULTRASONIC_ECHO_PIN);
ColorSensor colorSensor(COLOR_SENSOR_S0, COLOR_SENSOR_S1, COLOR_SENSOR_S2, COLOR_SENSOR_S3, COLOR_SENSOR_OUT);
GripperControl gripper(GRIPPER_PICKER, GRIPPER_ELBOW, GRIPPER_SHOULDER, GRIPPER_WAIST);
SteeringControl steering(STEERING_SERVO_PIN);

// Command callback
void command_callback(const void *msg_in) {
    const std_msgs__msg__String *msg = (const std_msgs__msg__String *)msg_in;
    String command = String(msg->data.data);

    if (command == "forward") {
        rearMotor.forward(255);
    } else if (command == "stop") {
        rearMotor.stop();
    }
}


void setup() {
    Serial.begin(115200);
    initializePins();  // Initialize all pins

    Serial.begin(115200);
    initializePins();

    // // Initialize Micro-ROS
    // set_microros_transports(SERIAL);
    allocator = rcl_get_default_allocator();
    rclc_support_init(&support, 0, NULL, &allocator);
    rclc_node_init_default(&node, "autonomous_robot", "", &support);

    // Create publishers
    rclc_publisher_init_default(&distance_publisher, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32), "/distance");
    rclc_publisher_init_default(&color_publisher, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String), "/color");

    // Create subscriber
    rclc_subscription_init_default(&command_subscriber, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String), "/command");

    // Create executor
    rclc_executor_init(&executor, &support.context, 1, &allocator);
    rclc_executor_add_subscription(&executor, &command_subscriber, &command_msg, &command_callback, ON_NEW_DATA);

}

void loop() {

    // Publish sensor data
    distance_msg.data = (int32_t)ultrasonicSensor.getDistance();
    rcl_publish(&distance_publisher, &distance_msg, NULL);

    strncpy(color_msg.data.data, colorSensor.getColor().c_str(), sizeof(color_msg.data.data) - 1);
    color_msg.data.data[sizeof(color_msg.data.data) - 1] = '\0';  // Ensure null-termination
    rcl_publish(&color_publisher, &color_msg, NULL);

    // Spin Micro-ROS executor
    rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
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