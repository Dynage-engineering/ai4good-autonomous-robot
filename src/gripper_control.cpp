#include <Arduino.h>
#include "autonomous_robot/gripper_control.h"
#include "pin_config.h" 


GripperControl::GripperControl(int pin1 = GRIPPER_PICKER, int pin2 = GRIPPER_ELBOW, int pin3 = GRIPPER_SHOULDER, int pin4 = GRIPPER_WAIST) {
    servo1_.attach(pin1);
    servo2_.attach(pin2);
    servo3_.attach(pin3);
    servo4_.attach(pin4);
}

void GripperControl::open() {
    servo1_.write(90);  // Example angles
    servo2_.write(90);
    servo3_.write(90);
    servo4_.write(90);
}

void GripperControl::close() {
    servo1_.write(0);  // Example angles
    servo2_.write(0);
    servo3_.write(0);
    servo4_.write(0);
}