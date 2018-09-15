#ifndef UTView_h
#define UTView_h

#include "Arduino.h"
#include "UTStack.h"
#include "UTTypes.h"

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "UTMain.h"
//#include <UTPing.h>

class UTView
{
    public:
        UTView() {componentPosition = 0;};
        void begin();
        bool isRunning();

        void handlePress(uint8_t i);

    private:
        uint16_t componentPosition;
        UTStack<UTComponent> components();
        UTMain *main;
        bool running;

        String stop = "stop";
        String microSeconds = "μs";

        void showSplashScreen();

        void switchView(view newView, uint8_t position);

        void handleMainEnterPress();
        void handleMenuEnterPress();
        void handleDelayEnterPress();
        void handleGainEnterPress();
        void handleRangeEnterPress();
        void handleCalibrateEnterPress();

        void setCursor(XYPos_t position);
};

#endif