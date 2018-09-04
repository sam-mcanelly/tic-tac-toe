#ifndef UTView_h
#define UTView_h

#include "Arduino.h"

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <UTPing.h>

#define OLED_RESET  4
#define OLED_ADDR   0x3C

#define MAIN_IO_COUNT 3
#define MENU_IO_COUNT 4
#define ADJUSTMENT_IO_COUNT 1

struct XYPos_t
{
    uint16_t x;
    uint16_t y;
};

enum view
{
    MAIN,
    MENU,
    CALIBRATE,
    RANGE,
    DELAY,
    GAIN
};

enum _input
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER
};

class UTView
{
    public:
        UTView();
        void begin();
        bool isRunning();

        void updateGraph();
        void handlePress(uint8_t i);

    private:
        bool running;
        int inputCursorPosition;

        String stop = "stop";
        String microSeconds = "μs";

        String mainViewStrings[MAIN_IO_COUNT] = {"menu", "start", "pause"};
        String menuViewStrings[MENU_IO_COUNT] = {"delay", "gain", "range", "calibration"};

        //main screen input positions
        XYPos_t menuPosition = {1, 54};
        XYPos_t startPosition = {45, 54};
        XYPos_t pausePosition = {95, 54};

        //menu screen input positions
        XYPos_t delayPosition = {2, 12};
        XYPos_t gainPosition = {2, 22};
        XYPos_t rangePosition = {2, 32};
        XYPos_t calibratePosition = {2, 42};


        XYPos_t mainInputPositions[MAIN_IO_COUNT] = {menuPosition, startPosition, pausePosition};
        XYPos_t menuInputPositions[MENU_IO_COUNT] = {delayPosition, gainPosition, rangePosition, calibratePosition};
        //XYPos_t adjustmentInputPositions[ADJUSTMENT_IO_COUNT] = ;

        view currentView;

        void showSplashScreen();

        void switchView(view newView, uint8_t position);

        void leftPress();
        void rightPress();
        void upPress();
        void downPress();
        void enterPress();

        void handleMainEnterPress();
        void handleMenuEnterPress();
        void handleDelayEnterPress();
        void handleGainEnterPress();
        void handleRangeEnterPress();
        void handleCalibrateEnterPress();

        void showMainView();
        void showMenuView();
        void showCalibrateView();
        void showDelayView();
        void showGainView();
        void showRangeView();

        void drawAdjustmentFrame();
        void clearAdjustmentFrame();

        void incrementDelay(bool up);
        void incrementGain(bool up); 

        void setCursor(XYPos_t position);

        void drawGraph();
        void drawMainViewButtons();
        void drawMenuViewButtons();
        void drawDelayAdjuster();

        void moveInputCursor(_input i);
        void moveMainCursor(_input i);
        void moveMenuCursor(_input i);
        void moveDelayCursor(_input i);
};

#endif