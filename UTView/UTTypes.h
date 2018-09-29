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
#define DOWN_PIN 5
#define RIGHT_PIN 6

#define GAIN_PIN A3
#define RANGE_PIN A2
#define OFFSET_PIN A1
#define INSPECT_PIN A0

#define MAIN_IO_COUNT 3
#define MENU_IO_COUNT 4
#define ADJUSTMENT_IO_COUNT 2
#define ADJUSTMENT_STRING_COUNT 2
#define ADJUSTMENT_VALUE_DIGIT_COUNT 4

#define FRAME_POINT_COUNT 100
#define FRAME_STORAGE_COUNT 30

#define MEASURMENT_VALUE_LENGTH 7

#include "Arduino.h"

const String micro_seconds = "uS";//"μs";
const String meters = "m";
const String centimeters = "cm";
const String decibal = "dB";

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

enum graph_state_t
{
    NORMAL,
    INSPECT,
    REPLAY
};

struct adjustment_params_t 
{
    float _delay;
    float _gain;
    float _range;

    uint8_t _delay_digits[4];
    uint8_t _gain_digits[4];
    uint8_t _range_digits[4];
};

#endif