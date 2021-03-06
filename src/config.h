// Copyright 2021 Peter Siegel psiegel@bu.edu

#ifndef CONFIG_H
#define CONFIG_H

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

#endif /* CONFIG_H */