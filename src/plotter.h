#ifndef PLOTTER_H
#define PLOTTER_H

#include <Arduino.h>
#include <AccelStepper.h>
#include <Servo.h>
#include "clock.h"

class Axis : public AccelStepper
{
public:
    Axis(int8_t, int, int);
    void moveMillimeters(float);
    void moveToMillimeters(float);
    float currentPositionMillimeters();
    void setSpeedMillimeters(float);
};

class Effector : public Servo
{
public:
    Effector(int);
    void position(int8_t);
};

class Plotter
{
public:
    Plotter();
    bool moveDone();
    void setSpeed(float);
    void home(float);
    void move(float, float);
    void moveTo(float, float);
    bool run();
    bool runSpeedToPosition();
    void drawDigit(Digit, float, float);
    void drawClock(Clock, float, float);

public:
    Axis *axisLeft;
    Axis *axisRight;
    Effector *effector;
    Clock *clock;
};

#endif /* PLOTTER_H */