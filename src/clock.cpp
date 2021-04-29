#include <Arduino.h>
#include <config.h>
#include "clock.h"

Digit::Digit()
{
    // A:
    segments[0].start = {DIGIT_WIDTH, DIGIT_HEIGHT};
    segments[0].end = {0, DIGIT_HEIGHT};

    // B:
    segments[1].start = {DIGIT_WIDTH, DIGIT_HEIGHT / 2};
    segments[1].end = {DIGIT_WIDTH, DIGIT_HEIGHT};

    // C:
    segments[2].start = {DIGIT_WIDTH, 0};
    segments[2].end = {DIGIT_WIDTH, DIGIT_HEIGHT / 2};

    // D:
    segments[3].start = {0, 0};
    segments[3].end = {DIGIT_WIDTH, 0};

    // E:
    segments[4].start = {0, DIGIT_HEIGHT / 2};
    segments[4].end = {0, 0};

    // F:
    segments[5].start = {0, DIGIT_HEIGHT};
    segments[5].end = {0, DIGIT_HEIGHT / 2};

    // G:
    segments[6].start = {0, DIGIT_HEIGHT / 2};
    segments[6].end = {DIGIT_WIDTH, DIGIT_HEIGHT / 2};

    for (int i = 0; i < NUM_SEGMENTS; i++)
    {
        segments[i].isActive = false;
    }
}

void Digit::setDigit(uint8_t digit)
{
    switch (digit)
    {
    case 0:
        segments[0].isActive = true;
        segments[1].isActive = true;
        segments[2].isActive = true;
        segments[3].isActive = true;
        segments[4].isActive = true;
        segments[5].isActive = true;
    case 1:
        segments[1].isActive = true;
        segments[2].isActive = true;
        break;

    case 2:
        segments[0].isActive = true;
        segments[1].isActive = true;
        segments[3].isActive = true;
        segments[4].isActive = true;
        segments[6].isActive = true;
        break;

    case 3:
        segments[0].isActive = true;
        segments[1].isActive = true;
        segments[2].isActive = true;
        segments[3].isActive = true;
        segments[6].isActive = true;
        break;

    case 4:
        segments[1].isActive = true;
        segments[2].isActive = true;
        segments[5].isActive = true;
        segments[6].isActive = true;
        break;

    case 5:
        segments[0].isActive = true;
        segments[2].isActive = true;
        segments[3].isActive = true;
        segments[5].isActive = true;
        segments[6].isActive = true;
        break;

    case 6:
        segments[0].isActive = true;
        segments[2].isActive = true;
        segments[3].isActive = true;
        segments[4].isActive = true;
        segments[5].isActive = true;
        segments[6].isActive = true;
        break;

    case 7:
        segments[0].isActive = true;
        segments[1].isActive = true;
        segments[2].isActive = true;
        break;

    case 8:
        segments[0].isActive = true;
        segments[1].isActive = true;
        segments[2].isActive = true;
        segments[3].isActive = true;
        segments[4].isActive = true;
        segments[5].isActive = true;
        segments[6].isActive = true;
        break;

    case 9:
        segments[0].isActive = true;
        segments[1].isActive = true;
        segments[2].isActive = true;
        segments[3].isActive = true;
        segments[5].isActive = true;
        segments[6].isActive = true;
        break;
    default:
        for (int i = 0; i < NUM_SEGMENTS; i++)
        {
            segments[i].isActive = true;
        }
        break;
    }
}

void Digit::reset()
{
    for (int i = 0; i < NUM_SEGMENTS; i++)
    {
        segments[i].isActive = false;
    }
}

Delimiter::Delimiter() {
    bottom.x_mm = 0;
    bottom.y_mm = (DIGIT_HEIGHT - DELIMITER_HEIGHT)/2;
    top.x_mm = 0;
    top.y_mm = DELIMITER_HEIGHT + bottom.y_mm;
}

Clock::Clock() {
    
};