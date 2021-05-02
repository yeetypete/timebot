# Timebot: The 2-DOF Parallel Plotting robot

Here you will find the program used to write the time to a whiteboard using a 2-DOF Parallel robot created in Boston University's ME360 course.

## Plotter Configuration
You can find the configuration file which controls various parameters and settings based on the geometry of the robot and the electronics setup in [src/config.h](src/config.h). The following parameters can be modified to suit various configurations:

```c++
#define CLOCK_NUM_DIGITS 4

#define EFFECTOR_PIN 9
#define EFFECTOR_TRAVEL_DEGREES 20
#define EFFECTOR_OFFSET_DEGREES 20
#define EFFECTOR_TRAVEL_TIME 200

#define STEPPER_1_PIN_1 2
#define STEPPER_1_PIN_2 5

#define STEPPER_2_PIN_1 3
#define STEPPER_2_PIN_2 6

#define STEPPER_MAX_SPEED 100.0   // mm/s

#define PITCH_DIAM_PULLEY 12.7 // mm
#define STEPS_PER_REV 800.0

#define PLOTTER_LINK_LENGTH 125 // mm
#define IDLER_WIDTH 52.85 // mm
#define ERASER_OFFSET 32.0 // mm

#define DIGIT_WIDTH 10.0 // mm
#define DIGIT_HEIGHT 20.0 // mm
#define DIGIT_SPACING 1.74 * DIGIT_WIDTH // mm
#define DELIMITER_HEIGHT 15.0 // mm
#define NUM_SEGMENTS 7
```

# Program Overview

The `Plotter` class (found in [src/plotter.h](src/plotter.h)) controls the motion of the robot. The methods contained in the `Plotter` class are listed below:

```c++
Plotter();
bool moveDone();
void setSpeed(float);
void home(float);
void move(float, float);
void moveTo(float, float);
bool run();
bool runSpeedToPosition();
void drawDigit(Digit, float, float);
void eraseDigit(Digit, float, float);
void drawClock(Clock *, float, float);
void eraseClock(Clock *, float, float);
void eraseBoard(float, float, float, float);
void drawDelimiter(Delimiter *, float, float);
```

The `Clock` class (found in [src/clock.h](src/clock.h)) stores geometric information that describes the layout of the alphanumeric clock which is plotted by the robot. The member variables stored in the `Clock` class are listed below:

```c++
class Clock {
    public:
    Clock();

    Digit digits[CLOCK_NUM_DIGITS];
    Delimiter delimiter;
    
};
```
The `Delimeter` and `Digit` classes (found in [src/clock.h](src/clock.h)) are used to define the geometry of the delimiter and digits in the clock alphanumeric display. The `Digit` and `Delimiter` classes are defined as follows:

```c++
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
```
Digits are made of segments consisting of a `Point` class storing the x and y coordinate. The start point and end point define a line segment. The `Point` and `Segment` classes are found in [src/clock.h](src/clock.h) and have the following structure:

```c++
struct Point {
    float x_mm;
    float y_mm;
};

struct Segment {
    Point start;
    Point end;
    bool isActive = false;
};
```
Copyright 2021 Peter Siegel psiegel@bu.edu