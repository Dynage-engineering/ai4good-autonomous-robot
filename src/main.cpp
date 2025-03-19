#include <Arduino.h>
#include "autonomous_robot/dc_motor.h"


DCMotor rearMotor(9, 8, 7);  // Rear motor

void setup(){
    Serial.begin(9600);
    rearMotor.forward(255);  // Move forward at full speed
    delay(2000);             // Move for 2 seconds
    rearMotor.stop();     // Stop the motor
}

void loop(){
    Serial.println("Hello World");
    delay(1000);
}