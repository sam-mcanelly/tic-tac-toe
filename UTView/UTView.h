/****************************************
 * 
 * Ultrasonic Flaw Detector - UTView
 * Author(s): Sam McAnelly, 
 * Oklahoma State University
 * ECEN 4013
 * 
 ****************************************/

#ifndef UTView_h
#define UTView_h

#include "Arduino.h"
#include "UTTypes.h"

#include <EEPROM.h>
#include <SPI.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#if(DISPLAY_TYPE == SSD_1306)
    #include <Adafruit_SSD1306.h>
#elif(DISPLAY_TYPE == ST_7735)
    #include <Adafruit_ST7735.h>
#endif

#include "UTMain.h"
#include "UTGraph.h"
#include "UTMenu.h"
#include "UTAdjuster.h"

class UTView
{
    public:
        UTView() {
            active_component_idx = 0;
            populateAdjustmentParams();
        };

        ~UTView() {
            Serial.println("destructing view...");
            delete display;
            delete graph;
            delete main;
            delete menu;
            delete delay_adjuster;
            delete gain_adjuster;
            delete range_adjuster;
        };

        void begin();

        boolean isRunning();

        void handlePress(input_t i);

    private:
        uint8_t active_component_idx;

        adjustment_params_t adjustment_parameters;

        UTDisplayWrapper<DISPLAY_TYPE_CLASS> *display;
        
        UTMain *main;
        UTGraph *graph;
        UTMenu *menu;
        UTAdjuster *delay_adjuster;
        UTAdjuster *gain_adjuster;
        UTAdjuster *range_adjuster;

        UTComponent *view_components[10];
        UTComponent *active_component;

        void showSplashScreen();

        void populateAdjustmentParams();

        void addView(UTComponent *new_view);
        void removeTopView();
        void exitToMainView();

        void redrawAll();
};

#endif