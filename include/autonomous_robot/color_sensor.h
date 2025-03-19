#include <StreamString.h>
#ifndef AUTONOMOUS_ROBOT_COLOR_SENSOR_H
#define AUTONOMOUS_ROBOT_COLOR_SENSOR_H

class ColorSensor {
public:
    ColorSensor(int s0, int s1, int s2, int s3, int out);
    String getColor();

private:
    int s0_, s1_, s2_, s3_, out_;
};

#endif