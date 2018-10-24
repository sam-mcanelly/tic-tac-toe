/****************************************
 * 
 * Ultrasonic Flaw Detector - UTComponent
 * Author(s): Sam McAnelly, 
 * Oklahoma State University
 * ECEN 4013
 * 
 ****************************************/

#ifndef UTComponent_h
#define UTComponent_h

#include "Arduino.h"
#include "UTTypes.h"
#include "UTDisplayWrapper.h"

#include <Wire.h>
#include <SPI.h>

class UTComponent 
{
    public:
        virtual void create(boolean show);
        virtual XYPos_t getCursorPositionLocation();
        virtual XYPos_t getPositionXY(uint8_t position);

        virtual ~UTComponent() {};

        uint8_t getCursorPosition() {
            return input_cursor_position;
        };

        virtual void changeCursorPosition(uint8_t new_position);

        virtual view_t buttonPress(input_t i) {
            switch(i) {
                case 0:
                    return upPress();
                case 1:
                    return downPress();
                case 2:
                    return leftPress();
                case 3:
                    return rightPress();
                case 4:
                    return enterPress();
                default:
                    return NONE;
            }   
        };

    protected:
        UTDisplayWrapper<DISPLAY_TYPE_CLASS> * display;

        uint8_t input_cursor_position = 0;

        virtual void setCursor(XYPos_t position);

        //these are pretty redundant so maybe remove them
        virtual view_t leftPress();
        virtual view_t rightPress();
        virtual view_t upPress();
        virtual view_t downPress();
        virtual view_t enterPress(); 

    private:       

};

#endif