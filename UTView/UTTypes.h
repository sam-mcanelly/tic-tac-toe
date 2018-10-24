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

#define _SCL 13 //sclk
#define _SDA 11 //mosi
#define _CS 10 //cs
#define _A0 9 //dc
#define _RST 8 //reset

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

#define DELAY_EEPROM_START 1
#define GAIN_EEPROM_START 5
#define RANGE_EEPROM_START 9

#define DEBUGGING_MODE true

#define SSD_1306 0
#define ST_7735  1

#define DISPLAY_TYPE 1 //change to SSD_1306 or ST_7735 value

#if(DISPLAY_TYPE == SSD_1306)
    #define CANVAS_WIDTH 128
    #define CANVAS_HEIGHT 51
    #define DISPLAY_TYPE_CLASS Adafruit_SSD1306
#elif(DISPLAY_TYPE == ST_7735)
    #define CANVAS_WIDTH 160
    #define CANVAS_HEIGHT 70
    #define DISPLAY_TYPE_CLASS Adafruit_ST7735
#endif

// Color definitions
// (redefined from the ST7735 lib)
#define	_BLACK   0x0000
#define	_BLUE    0x001F
#define	_RED     0xF800
#define	_GREEN   0x07E0
#define _CYAN    0x07FF
#define _MAGENTA 0xF81F
#define _YELLOW  0xFFE0  
#define _WHITE   0xFFFF

#include "Arduino.h"

const String micro_seconds = "uS";//"μs";
const String meters = "m";
const String centimeters = "cm";
const String decibal = "dB";

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

enum button_size_t
{
    SMALL,
    MEDIUM,
    LARGE
};

struct XYPos_t
{
    uint16_t x;
    uint16_t y;
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

struct button_params_t
{
    uint16_t w;     //width
    uint16_t h;     //height
    uint16_t r;     //radius
};

#if(DISPLAY_TYPE == SSD_1306)
     const struct button_params_t small_button = {0, 0, 0};
#elif(DISPLAY_TYPE == ST_7735)
    const struct button_params_t small_button = {40, 12, 2};
    const struct button_params_t medium_button = {30, 20, 15};
    const struct button_params_t large_button = {40, 30, 20};
#endif

#endif