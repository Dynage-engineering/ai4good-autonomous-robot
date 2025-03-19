#include <Arduino.h>
#include "autonomous_robot/dc_motor.h"
#include "pin_config.h"

DCMotor rearMotor(9, 8, 7);  // Rear motor

void setup(){
    initializePins();  //
}

void loop(){
    Serial.println("Hello World");
    delay(1000);
}