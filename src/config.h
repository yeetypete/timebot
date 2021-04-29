#ifndef CONFIG_H
#define CONFIG_H

#define CLOCK_NUM_DIGITS 4

#define EFFECTOR_PIN 10
#define EFFECTOR_TRAVEL_DEGREES 20.0
#define EFFECTOR_OFFSET_DEGREES 0.0

#define STEPPER_1_PIN_1 2
#define STEPPER_1_PIN_2 5

#define STEPPER_2_PIN_1 3
#define STEPPER_2_PIN_2 6

#define STEPPER_MAX_SPEED 100.0   // mm/s

#define PITCH_DIAM_PULLEY 12.7 // mm
#define STEPS_PER_REV 800.0

#define PLOTTER_LINK_LENGTH 125 // mm
#define IDLER_WIDTH 52.85 // mm
#define ERASER_OFFSET 24.0 // mm

#define DIGIT_WIDTH 15.0 // mm
#define DIGIT_HEIGHT 30.0 // mm
#define DIGIT_SPACING 1.25 * DIGIT_WIDTH
#define NUM_SEGMENTS 7

#endif /* CONFIG_H */