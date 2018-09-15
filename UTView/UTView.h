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
#include "UTGraph.h"
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
        UTStack<UTComponent*> components();
        UTMain *main;
        UTGraph *graph;

        UTComponent *view_components[2] = {main, graph};
        UTComponent *active_component;
        uint8_t active_component_idx = 0;
        //UTMenu *menu;
        bool running;

        String stop = "stop";
        String microSeconds = "μs";

        void showSplashScreen();

        // void handleMainEnterPress();
        // void handleMenuEnterPress();
        // void handleDelayEnterPress();
        // void handleGainEnterPress();
        // void handleRangeEnterPress();
        // void handleCalibrateEnterPress();
};

#endif