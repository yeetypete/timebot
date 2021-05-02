// Copyright 2021 Peter Siegel psiegel@bu.edu

#include <Arduino.h>
#include <AccelStepper.h>
#include <Servo.h>
#include <math.h>

#include "config.h"
#include "plotter.h"
#include "clock.h"

Axis::Axis(int8_t interface, int pin1, int pin2) : AccelStepper(interface, pin1, pin2)
{
  setSpeed(STEPPER_MAX_SPEED * STEPS_PER_REV / (PI * PITCH_DIAM_PULLEY));
  setMaxSpeed(STEPPER_MAX_SPEED * STEPS_PER_REV / (PI * PITCH_DIAM_PULLEY));
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

float Axis::currentPositionMillimeters()
{
  float millimeters = currentPosition() * (PI * PITCH_DIAM_PULLEY) / STEPS_PER_REV;
  return millimeters;
}

void Axis::setSpeedMillimeters(float millimeters)
{
  setSpeed(millimeters * STEPS_PER_REV / (PI * PITCH_DIAM_PULLEY));
}

Effector::Effector(){};

void Effector::position(int8_t position) // 0 = level, 1 = pen down, 2 = eraser down (pen up)
{
  if (position == 0)
  {
    write(90 - EFFECTOR_OFFSET_DEGREES); // center is 90 deg
    delay(EFFECTOR_TRAVEL_TIME);
  }
  else if (position == 1)
  {
    write(90 - EFFECTOR_OFFSET_DEGREES + EFFECTOR_TRAVEL_DEGREES);
    delay(EFFECTOR_TRAVEL_TIME);
  }
  else if (position == 2)
  {
    write(90 - EFFECTOR_OFFSET_DEGREES - EFFECTOR_TRAVEL_DEGREES);
    delay(EFFECTOR_TRAVEL_TIME);
  }
  else
    return;
}

Plotter::Plotter() : axisLeft(new Axis(AccelStepper::FULL2WIRE, STEPPER_1_PIN_1, STEPPER_1_PIN_2)),
                     axisRight(new Axis(AccelStepper::FULL2WIRE, STEPPER_2_PIN_1, STEPPER_2_PIN_2)),
                     effector(new Effector()){

                     };

bool Plotter::moveDone()
{
  return (axisLeft->distanceToGo() == 0) && (axisRight->distanceToGo() == 0);
}

void Plotter::setSpeed(float millimeters)
{
  axisLeft->setSpeedMillimeters(millimeters);
  axisRight->setSpeedMillimeters(millimeters);
}

void Plotter::home(float travel_mm)
{
  effector->position(2);
  axisLeft->moveMillimeters(travel_mm);
  axisRight->moveMillimeters(-travel_mm);

  axisLeft->setSpeedMillimeters(STEPPER_MAX_SPEED);
  axisRight->setSpeedMillimeters(STEPPER_MAX_SPEED);

  while (!moveDone())
  {
    axisLeft->runSpeedToPosition();
    axisRight->runSpeedToPosition();
  }

  int steps = (IDLER_WIDTH / 2) * STEPS_PER_REV / (PI * PITCH_DIAM_PULLEY);
  axisLeft->setCurrentPosition(-steps);
  axisRight->setCurrentPosition(steps);
}

void Plotter::move(float x_mm, float y_mm)
{
  if (y_mm > PLOTTER_LINK_LENGTH)
  {
    axisLeft->stop();
    axisRight->stop();
    while (true)
      ;
  }

  else if (fabs(x_mm) > PLOTTER_LINK_LENGTH)
  {
    axisLeft->stop();
    axisRight->stop();
    while (true)
      ;
  }

  float delta = sqrtf((PLOTTER_LINK_LENGTH - y_mm) * (PLOTTER_LINK_LENGTH + y_mm));
  float axisLeftPos = x_mm - delta;
  float axisRightPos = x_mm + delta;
  axisLeft->moveMillimeters(axisLeftPos);
  axisRight->moveMillimeters(axisRightPos);
}

void Plotter::moveTo(float x_mm, float y_mm)
{

  if (y_mm > PLOTTER_LINK_LENGTH)
  {
    axisLeft->stop();
    axisRight->stop();
    while (true)
      ;
  }

  else if (fabs(x_mm) > PLOTTER_LINK_LENGTH)
  {
    axisLeft->stop();
    axisRight->stop();
    while (true)
      ;
  }

  float delta = sqrtf((PLOTTER_LINK_LENGTH - y_mm) * (PLOTTER_LINK_LENGTH + y_mm));
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

bool Plotter::runSpeedToPosition()
{
  bool axisLeftStatus = axisLeft->runSpeedToPosition();
  bool axisRightStatus = axisRight->runSpeedToPosition();
  return axisLeftStatus && axisRightStatus;
}

void Plotter::drawDigit(Digit digit, float digit_loc_x_mm, float digit_loc_y_mm)
{
  for (int i = 0; i < NUM_SEGMENTS; i++)
  {
    if (digit.segments[i].isActive)
    {
      float x_mm = digit.segments[i].start.x_mm + digit_loc_x_mm;
      float y_mm = digit.segments[i].start.y_mm + digit_loc_y_mm;
      moveTo(x_mm, y_mm);
      setSpeed(STEPPER_MAX_SPEED);
      while (!moveDone())
        runSpeedToPosition();

      effector->position(1); // put pen down

      x_mm = digit.segments[i].end.x_mm + digit_loc_x_mm;
      y_mm = digit.segments[i].end.y_mm + digit_loc_y_mm;
      moveTo(x_mm, y_mm);
      setSpeed(STEPPER_MAX_SPEED);
      while (!moveDone())
        runSpeedToPosition();

      effector->position(2); // lift pen up
    }
  }
}

void Plotter::eraseDigit(Digit digit, float digit_loc_x_mm, float digit_loc_y_mm)
{
  for (int i = 0; i < NUM_SEGMENTS; i++)
  {
    if (digit.segments[i].isActive)
    {
      float x_mm = digit.segments[i].start.x_mm + digit_loc_x_mm - ERASER_OFFSET;
      float y_mm = digit.segments[i].start.y_mm + digit_loc_y_mm;
      moveTo(x_mm, y_mm);
      setSpeed(STEPPER_MAX_SPEED);
      while (!moveDone())
        runSpeedToPosition();

      effector->position(2);

      x_mm = digit.segments[i].end.x_mm + digit_loc_x_mm - ERASER_OFFSET;
      y_mm = digit.segments[i].end.y_mm + digit_loc_y_mm;
      moveTo(x_mm, y_mm);
      setSpeed(STEPPER_MAX_SPEED);
      while (!moveDone())
        runSpeedToPosition();

      effector->position(2);
    }
  }
}


void Plotter::drawClock(Clock *clock, float clock_loc_x_mm, float clock_loc_y_mm)
{
  float x_mm = clock_loc_x_mm;
  float y_mm = clock_loc_y_mm;
  for (int i = 0; i < CLOCK_NUM_DIGITS; i++)
  {
    drawDigit(clock->digits[i], x_mm, y_mm);

    if (i == 1)
    {
      // draw delimiter
      float delim_offset_x_mm = DIGIT_SPACING;
      x_mm += delim_offset_x_mm;
      drawDelimiter(&clock->delimiter, x_mm, y_mm);
    };
      x_mm += DIGIT_SPACING;
  }
}

void Plotter::eraseClock(Clock *clock, float clock_loc_x_mm, float clock_loc_y_mm)
{
  float x_mm = clock_loc_x_mm - ERASER_OFFSET;
  float y_mm = clock_loc_y_mm;
  for (int i = 0; i < CLOCK_NUM_DIGITS; i++)
  {
    x_mm += DIGIT_SPACING;
    eraseDigit(clock->digits[i], x_mm, y_mm);
  }
}

void Plotter::eraseBoard(float x_1_mm, float y_1_mm, float x_2_mm, float y_2_mm) {
  
}


void Plotter::drawDelimiter(Delimiter *delim, float delim_loc_x_mm, float delim_loc_y_mm)
{
  float x_mm = delim->bottom.x_mm + delim_loc_x_mm;
  float y_mm = delim->bottom.y_mm + delim_loc_y_mm;

  moveTo(x_mm, y_mm);
  setSpeed(STEPPER_MAX_SPEED);
  while (!moveDone())
    runSpeedToPosition();

  effector->position(1);
  effector->position(2);

  x_mm += delim->top.x_mm;
  y_mm += delim->top.y_mm;

  moveTo(x_mm, y_mm);
  setSpeed(STEPPER_MAX_SPEED);
  while (!moveDone())
    runSpeedToPosition();

  effector->position(1);
  effector->position(2);
}
