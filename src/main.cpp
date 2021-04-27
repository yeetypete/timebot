#include <Arduino.h>
#include <AccelStepper.h>
#include <Servo.h>
#include <math.h>
#include "plotter.h"
#include "alphanumeric.h"

#define EFFECTOR_PIN 10
#define EFFECTOR_TRAVEL_DEGREES 20
#define EFFECTOR_OFFSET_DEGREES 0

#define STEPPER_1_PIN_1 2
#define STEPPER_1_PIN_2 5

#define STEPPER_2_PIN_1 3
#define STEPPER_2_PIN_2 6

#define STEPPER_MAX_SPEED 100   // mm/s
#define STEPPER_MAX_ACCEL 20000 // mm/s^2

#define PITCH_DIAM_PULLEY 12.7 // mm
#define STEPS_PER_REV 400

#define PLOTTER_LINK_LENGTH 75 // mm
//#define IDLER_WIDTH = 40 // mm

Axis::Axis(int8_t interface, int pin1, int pin2) : AccelStepper(interface, pin1, pin2)
{
  setMaxSpeed(STEPPER_MAX_SPEED * (STEPS_PER_REV / (PI * PITCH_DIAM_PULLEY)));
  setAcceleration(STEPPER_MAX_ACCEL * (STEPS_PER_REV / (PI * PITCH_DIAM_PULLEY)));
};

void Axis::moveMillimeters(float millimeters)
{
  int steps = millimeters * STEPS_PER_REV / (PI * PITCH_DIAM_PULLEY);
  move(steps);
};

void Axis::moveToMillimeters(float millimeters)
{
  int steps = millimeters * STEPS_PER_REV / (PI * PITCH_DIAM_PULLEY);
  moveTo(steps);
};

Effector::Effector(int pin)
{
  attach(pin);
};

void Effector::select(int8_t position) {
  if (position == 0) {
    write(90 - EFFECTOR_OFFSET_DEGREES); // center is 90 deg
  }
  if (position == 1) {
    write(90 - EFFECTOR_OFFSET_DEGREES + EFFECTOR_TRAVEL_DEGREES);
  }
  if (position == 2) {
    write(90 - EFFECTOR_OFFSET_DEGREES - EFFECTOR_TRAVEL_DEGREES);
  }
}

Plotter::Plotter() : axisLeft(new Axis(AccelStepper::FULL2WIRE, STEPPER_1_PIN_1, STEPPER_1_PIN_2)),
                     axisRight(new Axis(AccelStepper::FULL2WIRE, STEPPER_2_PIN_1, STEPPER_2_PIN_2)),
                     effector(new Effector(EFFECTOR_PIN)){

                     };

void Plotter::home(float travel_mm)
{
  axisLeft->moveMillimeters(travel_mm);
  axisRight->moveMillimeters(-travel_mm);

  while (run())
    ;

  axisLeft->setCurrentPosition(0);
  axisRight->setCurrentPosition(0);
}

void Plotter::move(float x_mm, float y_mm)
{
  if (y_mm > PLOTTER_LINK_LENGTH)
  {
    // axisLeft->stop();
    // axisRight->stop();
    return;
  }

  if (x_mm > PLOTTER_LINK_LENGTH || x_mm < -PLOTTER_LINK_LENGTH)
  {
    // axisLeft->stop();
    // axisRight->stop();
    return;
  }
  float delta = sqrtf(2 * powf(PLOTTER_LINK_LENGTH, 2) - 2 * powf(y_mm, 2)) / 2;
  float axisLeftPos = x_mm - delta;
  float axisRightPos = x_mm + delta;
  axisLeft->moveMillimeters(axisLeftPos);
  axisRight->moveMillimeters(axisRightPos);
}

void Plotter::moveTo(float x_mm, float y_mm)
{
  if (y_mm > PLOTTER_LINK_LENGTH)
    return;

  float delta = sqrtf(2 * powf(PLOTTER_LINK_LENGTH, 2) - 2 * powf(y_mm, 2)) / 2;
  float axisLeftPos = x_mm - delta;
  float axisRightPos = x_mm + delta;
  axisLeft->moveToMillimeters(axisLeftPos);
  axisRight->moveToMillimeters(axisRightPos);
}

bool Plotter::run()
{
  bool axisLeftStatus = axisLeft->run();
  bool axisRightStatus = axisRight->run();
  return axisLeftStatus && axisRightStatus;
}

Plotter plotter;

void setup()
{
  Serial.begin(9600);
  plotter.home(PLOTTER_LINK_LENGTH * 2);
  delay(1000);
}

void loop()
{
  plotter.moveTo(10, 20);
  while (plotter.run())
    ;
  plotter.moveTo(40, 20);
  while (plotter.run())
    ;
  while (true)
    ;
  plotter.effector->select(1);
  delay(100);
}