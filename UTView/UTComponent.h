#ifndef UTComponent_h
#define UTComponent_h

#include "Arduino.h"
#include "UTView.h"

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class UTComponent 
{
    public:
        virtual void create() = 0;
        virtual void destroy() = 0;

        void getCursorPosition() {
            return inputCursorPosition;
        };
        void setCursorPosition(uint8_t newPosition) {
            inputCursorPosition = input;
        };

        void buttonPress(_input i) {
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
        Adafruit_GFX *display;
        uint8_t inputCursorPosition;

        virtual void moveInputCursor(_input i) = 0;

        virtual void leftPress() = 0;
        virtual void rightPress() = 0;
        virtual void upPress() = 0;
        virtual void downPress() = 0;
        virtual void enterPress() = 0; 

    private:       

};

#endif