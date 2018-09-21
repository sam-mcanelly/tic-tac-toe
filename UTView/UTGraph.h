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
        UTGraph(Adafruit_SSD1306 *_display) {
            display = _display;
            running = false;

            for(int i = 0; i < 10; i++) {
                for(int j = 0; j < 100; j++) {
                    frames[i][j] = 0;
                }
            }
        };
        void create(boolean show);
        void update();
        void stop();

        void renderCurrentFrame();
        void runDemo();

        XYPos_t getCursorPositionLocation();
        XYPos_t getPositionXY(uint8_t position);

        void changeCursorPosition(uint8_t position);
        void setCursor(XYPos_t position);

        boolean isRunning();
    private:
        boolean running;
        double frames[10][100];
        double *current_frame;

        void checkButtons();

        view_t leftPress();
        view_t rightPress();
        view_t upPress();
        view_t downPress();
        view_t enterPress(); 

        void drawBoundaries(); 
};

#endif