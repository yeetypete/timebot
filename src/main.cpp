#include <Arduino.h>
#include <AccelStepper.h>
#include <math.h>
#include "plotter.h"

#define STEPPER_1_PIN_1 2
#define STEPPER_1_PIN_2 5

#define STEPPER_2_PIN_1 3
#define STEPPER_2_PIN_2 6

#define STEPPER_MAX_SPEED 100  // mm/s
#define STEPPER_MAX_ACCEL 20000 // mm/s^2

#define PITCH_DIAM_PULLEY 12.7 // mm
#define STEPS_PER_REV 400

#define PLOTTER_LINK_LENGTH 75 // mm

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

Plotter::Plotter() : axisLeft(new Axis(AccelStepper::FULL2WIRE, STEPPER_1_PIN_1, STEPPER_1_PIN_2)),
axisRight(new Axis(AccelStepper::FULL2WIRE, STEPPER_2_PIN_1, STEPPER_2_PIN_2)) {

};


void Plotter::calibrate(float travel_mm) {
  axisLeft->moveMillimeters(travel_mm);
  axisRight->moveMillimeters(-travel_mm);

  while (axisLeft->run() && axisRight->run());

  axisLeft->setCurrentPosition(0);
  axisRight->setCurrentPosition(0);
}

void Plotter::moveTo(float x_mm, float y_mm) {
  
}
void Plotter::move(float x_mm, float y_mm) {
  
}
Plotter plotter;

void setup()
{
  Serial.begin(9600);
  plotter.calibrate(100);
}

void loop()
{

}