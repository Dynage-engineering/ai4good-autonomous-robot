#ifndef AUTONOMOUS_ROBOT_ULTRASONIC_SENSOR_H
#define AUTONOMOUS_ROBOT_ULTRASONIC_SENSOR_H

class UltrasonicSensor {
public:
    UltrasonicSensor(int triggerPin, int echoPin);
    float getDistance();

private:
    int triggerPin_;
    int echoPin_;
};

#endif