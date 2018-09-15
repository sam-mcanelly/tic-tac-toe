#ifndef UTMain_h
#define UTMain_h

#include "UTComponent.h"
#include "UTGraph.h"

class UTMain : public UTComponent {
    public:
        UTMain(Adafruit_SSD1306 *_display){
            display = _display;
            graphActive = false;
            //graph = new UTGraph(_display);
        }

        ~UTMain() override {
            delete graph;
        }

        void create();

        XYPos_t getCursorPositionLocation();
        XYPos_t getPositionXY(uint8_t position);

        void buttonPress(_input i);
    private:
        UTGraph *graph;
        boolean graphActive; //are we currently interfacing with the graph?

        //main screen input positions
        XYPos_t menuPosition = {1, 54};
        XYPos_t startPosition = {45, 54};
        XYPos_t pausePosition = {95, 54};

        XYPos_t mainInputPositions[MAIN_IO_COUNT] = {menuPosition, startPosition, pausePosition};

        String mainViewStrings[MAIN_IO_COUNT] = {"menu", "start", "pause"};

        void moveInputCursor(_input i);

        void leftPress();
        void rightPress();
        void upPress();
        void downPress();
        void enterPress(); 

        void drawMainViewButtons();
};

#endif