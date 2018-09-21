/****************************************
 * 
 * Ultrasonic Flaw Detector - UTGraph
 * Author(s): Sam McAnelly, 
 * Oklahoma State University
 * ECEN 4013
 * 
 ****************************************/

#ifndef UTGraph_h
#define UTGraph_h

#include "UTComponent.h"

class UTGraph : public UTComponent {
    public:
        UTGraph(Adafruit_SSD1306 *_display) {display = _display;};
        void create(boolean show);

        XYPos_t getCursorPositionLocation();
        XYPos_t getPositionXY(uint8_t position);

        void changeCursorPosition(uint8_t position);
        void setCursor(XYPos_t position);
    private:

        view_t leftPress();
        view_t rightPress();
        view_t upPress();
        view_t downPress();
        view_t enterPress(); 
};

#endif