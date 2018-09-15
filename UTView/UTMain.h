/****************************************
 * 
 * Ultrasonic Flaw Detector - UTMain
 * Author(s): Sam McAnelly, 
 * Oklahoma State University
 * ECEN 4013
 * 
 ****************************************/

#ifndef UTMain_h
#define UTMain_h

#include "UTComponent.h"
#include "UTGraph.h"

class UTMain : public UTComponent {
    public:
        UTMain(Adafruit_SSD1306 *_display, UTGraph *_graph){
            display = _display;
            graphActive = false;
            graph = _graph;
        }

        ~UTMain() override {
            delete graph;
        }

        void create();
        XYPos_t getCursorPositionLocation();
        XYPos_t getPositionXY(uint8_t position);

        void changeCursorPosition(uint8_t new_position);

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

        void setCursor(XYPos_t position);

        void leftPress();
        void rightPress();
        void upPress();
        void downPress();
        void enterPress(); 

        void drawMainViewButtons();
};

#endif