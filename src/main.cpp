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
  for (int i = 0; i < CLOCK_NUM_DIGITS; i++)
  {
    clock.digits[i].setDigit(i + 1);
  }
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