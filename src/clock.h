#ifndef CLOCK_H
#define CLOCK_H
#include <Arduino.h>
#include "config.h"

struct Point {
    float x_mm;
    float y_mm;
};

struct Segment {
    Point start;
    Point end;
    bool isActive = false;
};

class Digit {
    public:
    Digit();

    public:
    void setDigit(uint8_t);
    void reset();
    Segment segments[NUM_SEGMENTS];
};

class Delimiter {
    public:
    Delimiter();

    public:
    Point bottom;
    Point top;
};

class Clock {
    public:
    Clock();

    Digit digits[CLOCK_NUM_DIGITS];
    Delimiter delimiter;
    
};

#endif /* CLOCK_H */
