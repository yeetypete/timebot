// Copyright 2021 Peter Siegel psiegel@bu.edu

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
  delay(2500);

  clock.digits[0].setDigit(1);
  clock.digits[1].setDigit(2);
  clock.digits[2].setDigit(3);
  clock.digits[3].setDigit(4);

  plotter.effector->attach(EFFECTOR_PIN);
  plotter.home(PLOTTER_LINK_LENGTH);
}

void loop()
{
  plotter.drawClock(&clock, -40, 70);
  plotter.eraseClock(&clock, -40, 70);
  while (true)
    ;
}