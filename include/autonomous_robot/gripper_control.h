#ifndef AUTONOMOUS_ROBOT_GRIPPER_CONTROL_H
#define AUTONOMOUS_ROBOT_GRIPPER_CONTROL_H

#include <ESP32Servo.h>

class GripperControl {
public:
    GripperControl(int pin1, int pin2, int pin3, int pin4);
    void open();
    void close();

private:
    Servo servo1_, servo2_, servo3_, servo4_;
};

#endif