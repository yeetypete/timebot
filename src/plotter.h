#ifndef PLOTTER_H
#define PLOTTER_H

#include <Arduino.h>
#include <AccelStepper.h>

class Axis : public AccelStepper
{
public:
    Axis(int8_t, int, int);
    void moveMillimeters(float);
    void moveToMillimeters(float);
};

class Plotter
{
public:
    Plotter();
    void calibrate(float);
    void moveTo(float, float);
    void move(float, float);

public:
    Axis *axisLeft;
    Axis *axisRight;
};

#endif /* PLOTTER_H */