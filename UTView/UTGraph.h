#ifndef UTGraph_h
#define UTGraph_h

#include "UTComponent.h"

class UTGraph : public UTComponent {
    public:
        UTGraph(Adafruit_SSD1306 *_display) {display = _display;};
        void create();
    private:
        void leftPress();
        void rightPress();
        void upPress();
        void downPress();
        void enterPress(); 
};

#endif