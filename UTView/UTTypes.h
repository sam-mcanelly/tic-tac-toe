/****************************************
 * 
 * Ultrasonic Flaw Detector - UTTypes
 * Author(s): Sam McAnelly, 
 * Oklahoma State University
 * ECEN 4013
 * 
 ****************************************/

#ifndef UTTypes_h
#define UTTypes_h

#define OLED_RESET  4
#define OLED_ADDR   0x3C

#define MAX_COMPONENT_IDX 9

#define IO_COUNT 5
#define LEFT_PIN 2
#define ENTER_PIN 3
#define UP_PIN 4
#define RIGHT_PIN 5
#define DOWN_PIN 6

#define MAIN_IO_COUNT 3
#define MENU_IO_COUNT 4
#define ADJUSTMENT_IO_COUNT 2
#define ADJUSTMENT_STRING_COUNT 2
#define ADJUSTMENT_VALUE_DIGIT_COUNT 4

#include "Arduino.h"

struct XYPos_t
{
    uint16_t x;
    uint16_t y;
};

enum view_t
{
    MAIN,
    MENU,
    CALIBRATE,
    RANGE,
    DELAY,
    GAIN,
    NONE,
    BACK
};

enum input_t
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER
};

struct adjustment_params_t 
{
    double _delay;
    double _gain;
    double _range;

    uint8_t _delay_digits[4];
    uint8_t _gain_digits[4];
    uint8_t _range_digits[4];
};

#endif