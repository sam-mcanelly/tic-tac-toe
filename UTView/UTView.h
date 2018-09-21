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
#include "UTMenu.h"

class UTView
{
    public:
        UTView() {active_component_idx = 0;};
        void begin();
        bool isRunning();

        void handlePress(input_t i);

    private:
        uint8_t active_component_idx;
        bool running;
        
        UTMain *main;
        UTGraph *graph;
        UTMenu *menu;

        UTComponent *view_components[10];
        UTComponent *active_component;

        String stop = "stop";
        String microSeconds = "μs";

        void showSplashScreen();

        void addView(UTComponent *new_view);
        void removeTopView();
        void exitToMainView();

        void redrawAll();
};

#endif