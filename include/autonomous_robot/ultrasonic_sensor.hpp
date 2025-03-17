#ifndef AUTONOMOUS_ROBOT_ULTRASONIC_SENSOR_HPP
#define AUTONOMOUS_ROBOT_ULTRASONIC_SENSOR_HPP

class UltrasonicSensor {
public:
    UltrasonicSensor();
    void setDistance(float distance);
    float getDistance();

private:
    float distance_;
};

#endif // AUTONOMOUS_ROBOT_ULTRASONIC_SENSOR_HPP
