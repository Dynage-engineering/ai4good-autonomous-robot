#ifndef AUTONOMOUS_ROBOT_DC_MOTOR_H
#define AUTONOMOUS_ROBOT_DC_MOTOR_H

class DCMotor {
public:
    DCMotor(int enablePin, int in1Pin, int in2Pin);
    void forward(int speed);
    void backward(int speed);
    void stop();

private:
    int enablePin_;
    int in1Pin_;
    int in2Pin_;
};

#endif