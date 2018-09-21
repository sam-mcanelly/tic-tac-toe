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

#define MAIN_IO_COUNT 3
#define MENU_IO_COUNT 4
#define ADJUSTMENT_IO_COUNT 1

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
    NONE
};

enum input_t
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER
};

#endif