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

#include <math.h>
#include "UTComponent.h"

class UTGraph : public UTComponent {
    public:
        UTGraph(Adafruit_SSD1306 *_display, adjustment_params_t * _parameters) {
            display = _display;
            adjustment_parameters = _parameters;
            running = false;
            gain = 1.0;
            range = 1.0;

            for(int i = 0; i < 10; i++) {
                for(int j = 0; j < 100; j++) {
                    frames[i][j].x = 0.0;
                    frames[i][j].y = 0.0;
                }
            }
        };
        void create(boolean show);
        void update();
        void stop();

        void nextFrame(XYPos_t values[100]);
        void renderCurrentFrame();
        void runDemo();

        XYPos_t getCursorPositionLocation();
        XYPos_t getPositionXY(uint8_t position);

        void changeCursorPosition(uint8_t position);
        void setCursor(XYPos_t position);

        boolean isRunning();
    private:
        boolean running;
        XYPos_t frames[10][126];
        int current_frame_idx = 0;
        double gain;
        double range;
        double offset;

        XYPos_t gain_position = {1, 54};
        XYPos_t range_position = {40, 54};
        XYPos_t offset_position = {90, 54};

        adjustment_params_t *adjustment_parameters;

        void checkButtons();
        void checkPots();

        view_t leftPress();
        view_t rightPress();
        view_t upPress();
        view_t downPress();
        view_t enterPress(); 

        void drawBoundaries(); 
        void clearParameterTray();
        void drawParameters();
};

#endif