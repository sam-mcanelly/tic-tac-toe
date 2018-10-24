/****************************************
 * 
 * Ultrasonic Flaw Detector - UTMenu
 * Author(s): Sam McAnelly, 
 * Oklahoma State University
 * ECEN 4013
 * 
 ****************************************/

#ifndef UTMenu_h
#define UTMenu_h

#include "UTComponent.h"
#include "UTGraph.h"

class UTMenu : public UTComponent {
    public:
        UTMenu(UTDisplayWrapper<DISPLAY_TYPE_CLASS> *_display){
            display = _display;
        }

        void create(boolean show);
        XYPos_t getCursorPositionLocation();
        XYPos_t getPositionXY(uint8_t position);

        void changeCursorPosition(uint8_t new_position);
    private:

        //menu screen input positions
        #if(DISPLAY_TYPE == SSD_1306)
            XYPos_t delayPosition = {2, 12};
            XYPos_t gainPosition = {2, 22};
            XYPos_t rangePosition = {2, 32};
            XYPos_t calibratePosition = {2, 42};
        #elif(DISPLAY_TYPE == ST_7735)
            XYPos_t delayPosition = {47, 17};
            XYPos_t gainPosition = {47, 27};
            XYPos_t rangePosition = {47, 37};
            XYPos_t calibratePosition = {47, 47};
        #endif

        XYPos_t menuInputPositions[MENU_IO_COUNT] = {delayPosition, gainPosition, rangePosition, calibratePosition};
        String menuViewStrings[MENU_IO_COUNT] = {"delay", "gain", "range", "calibration"};

        void setCursor(XYPos_t position);

        view_t leftPress();
        view_t rightPress();
        view_t upPress();
        view_t downPress();
        view_t enterPress(); 

        void drawMenuContainer();
        void drawMenuButtons();
};

#endif