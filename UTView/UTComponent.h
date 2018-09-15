#ifndef UTComponent_h
#define UTComponent_h

#include "Arduino.h"
#include "UTTypes.h"

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class UTComponent 
{
    public:
        virtual void create();
        virtual XYPos_t getCursorPositionLocation();
        virtual XYPos_t getPositionXY(uint8_t position) = 0;

        virtual ~UTComponent();

        uint8_t getCursorPosition() {
            return inputCursorPosition;
        };

        void setCursorPosition(uint8_t newPosition) {
            inputCursorPosition = newPosition;
            setCursor(getPositionXY(newPosition));
        };

        void setCursor(XYPos_t position) {
            //sets cursor to draw, not input cursor
            display->setCursor(position.x, position.y);
        }

        virtual void buttonPress(_input i) {
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
            }   
        };

    protected:
        Adafruit_SSD1306 *display;
        uint8_t inputCursorPosition;

        virtual void moveInputCursor(_input i);

        //these are pretty redundant so maybe remove them
        virtual void leftPress();
        virtual void rightPress();
        virtual void upPress();
        virtual void downPress();
        virtual void enterPress(); 

    private:       

};

#endif