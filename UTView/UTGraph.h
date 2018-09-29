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
        UTGraph(Adafruit_SSD1306 *_display, adjustment_params_t * _parameters) {
            display = _display;
            adjustment_parameters = _parameters;
            running = false;
            inspecting = false;
            active = false;
            gain = 1.0;
            range = 1.0;
            lower_bound = 0;

            for(int i = 0; i < FRAME_STORAGE_COUNT; i++) {
                for(int j = 0; j < FRAME_POINT_COUNT; j++) {
                    frames[i][j].x = 0;
                    frames[i][j].y = 0;
                }
            }
        };

        void create(boolean show);
        void stop();
        void exit();

        void nextFrame(XYPos_t values[100]);
        void renderCurrentFrame();
        void exportToSerial();
        void runDemo();

        XYPos_t getCursorPositionLocation();
        XYPos_t getPositionXY(uint8_t position);

        void changeCursorPosition(uint8_t position);
        void setCursor(XYPos_t position);

        boolean isActive();
        boolean isRunning();
    private:
        boolean running;
        boolean inspecting;
        boolean active;

        int current_frame_idx = 0;

        float gain;
        float range;
        float offset;
        float inspect;
        float inspect_x;
        float inspect_y;

        uint16_t lower_bound;
        uint16_t upper_bound;

        float analog_common_factor = 0.00097847;

        #if (DEBUGGING_MODE == true)
            int fps = 0;
            int frame_count = 0;
            long previous_millis = 0;
        #endif

        XYPos_t frames[FRAME_STORAGE_COUNT][FRAME_POINT_COUNT];

        //canvas_data[0] is x,y coordinates of top left corner
        //canvas_data[1] is width and height of canvas
        XYPos_t canvas_data[2] = {{1, 0},{128, 50}};

        //bottom tray position data 
        XYPos_t gain_position = {2, 54};
        XYPos_t distance_range_position = {40, 54};
        XYPos_t magnitude_offset_position = {85, 54};

        adjustment_params_t *adjustment_parameters;

        void checkButtonsWhileRunning();
        void checkPots();

        view_t leftPress();
        view_t rightPress();
        view_t upPress();
        view_t downPress();
        view_t enterPress(); 

        void drawBoundaries(); 
        void clearGraph();
        void drawParameterTray();
        void drawParameters();
        void drawInspectionPointer();

        void formatDisplayStringMetric(char * buffer, float value);
};

#endif