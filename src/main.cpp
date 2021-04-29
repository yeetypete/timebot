#include <Arduino.h>
#include <AccelStepper.h>
#include <Servo.h>
#include <math.h>
#include "plotter.h"
#include "clock.h"
#include "config.h"

Plotter plotter;
Clock clock;

void setup()
{
  plotter.home(PLOTTER_LINK_LENGTH);
  for (int i = 0; i < CLOCK_NUM_DIGITS; i++) {
    clock.digits[i].setDigit(i + 1);
  }
  delay(1000);
}

void loop()
{
  //plotter.drawDigit(clock.digits[0], 0, 75);
  plotter.drawClock(clock, -75, 50);
}

  // plotter.moveTo(0, 80);
  // plotter.setSpeed(STEPPER_MAX_SPEED);
  // while(!plotter.moveDone()) {
  //   plotter.runSpeedToPosition();
  // }
  // plotter.moveTo(20, 80);
  // plotter.setSpeed(STEPPER_MAX_SPEED);
  // while(!plotter.moveDone()) {
  //   plotter.runSpeedToPosition();
  // }
  //   plotter.moveTo(20, 100);
  // plotter.setSpeed(STEPPER_MAX_SPEED);
  // while(!plotter.moveDone()) {
  //   plotter.runSpeedToPosition();
  // }
  //   plotter.moveTo(0, 100);
  // plotter.setSpeed(STEPPER_MAX_SPEED);
  // while(!plotter.moveDone()) {
  //   plotter.runSpeedToPosition();
  // }
  

/*
  plotter.axisLeft->moveToMillimeters(10);
  plotter.axisLeft->setSpeedMillimeters(STEPPER_MAX_SPEED);
  while (plotter.axisLeft->distanceToGo() != 0)
    plotter.axisLeft->runSpeedToPosition();
  delay(500);
  plotter.axisLeft->moveToMillimeters(-10);
  plotter.axisLeft->setSpeedMillimeters(STEPPER_MAX_SPEED);
  while (plotter.axisLeft->distanceToGo() != 0)
    plotter.axisLeft->runSpeedToPosition();
  delay(500);
*/