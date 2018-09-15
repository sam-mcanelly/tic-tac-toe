#ifndef UTGraph_h
#define UTGraph_h

#include "UTComponent.h"

class UTGraph : public UTComponent {
    public:
        UTGraph(Adafruit_SSD1306 *_display) {display = _display;};
        void create();

        XYPos_t getCursorPositionLocation();
        XYPos_t getPositionXY(uint8_t position);

        void changeCursorPosition(uint8_t position);
        void setCursor(XYPos_t position);
    private:
        void moveInputCursor(_input i);

        void leftPress();
        void rightPress();
        void upPress();
        void downPress();
        void enterPress(); 
};

#endif