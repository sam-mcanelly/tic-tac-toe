/****************************************
 * 
 * Ultrasonic Flaw Detector - UTGraph
 * Author(s): Sam McAnelly, 
 * Oklahoma State University
 * ECEN 4013
 * 
 ****************************************/
#include <math.h>
#include <string>

#include "UTGraph.h"

/*
 * 
 * 
 *      Public Functions
 * 
 * 
 * */

void UTGraph::create(boolean show) {
    drawBoundaries();

    #if(DISPLAY_TYPE == ST_7735)
        drawParameterTray();
        drawParameters();
    #endif

    upper_bound = adjustment_parameters->_range;

    if(show)
        display->display();
}

//stop rendering
void UTGraph::stop() {
    inspecting = false;
    running = false;
}

//make graph inactive
void UTGraph::exit() {
    active = false;
}

//need to send with uint16_t measurements
//that are in millimeters
void UTGraph::nextFrame(XYPos_t values[FRAME_POINT_COUNT]) {
    
    #if (DEBUGGING_MODE == true)
        unsigned long current_millis = millis();
        //update fps if it's been a second 
        if(current_millis - previous_millis > 1000) {
            fps = frame_count;
            frame_count = 0;
            previous_millis = current_millis;
        } else {
            frame_count++;
        }
    #endif

    //update current frame index in history buffer
    current_frame_idx += 1;
    if(current_frame_idx > FRAME_STORAGE_COUNT - 1) {
        current_frame_idx = 0;
    }

    //fill history buffer with frames that were just received
    for(int i = 0; i < FRAME_POINT_COUNT; i++) {
        frames[current_frame_idx][i] = values[i];
    }

    checkButtonsWhileRunning();
    renderCurrentFrame();

    if(inspecting) drawInspectionPointer();

    // check potentiometers and draw parameters every other frame
    if(current_frame_idx % 2 == 0) {
        checkPots();
        drawParameters();
    }

    display->display();
}

void UTGraph::renderCurrentFrame() {
    clearGraph();

    //draw fps
    #if(DEBUGGING_MODE == true)
        if(isRunning()) {
            #if(DISPLAY_TYPE == SSD_1306)
                display->setCursor(95, 0);
            #elif(DISPLAY_TYPE == ST_7735)
                display->setCursor(130, 0);
            #endif
            display->setTextColor(_WHITE, _BLACK);
            display->print(fps);
            display->print("fps");
        }
    #endif

    #if(DISPLAY_TYPE == SSD_1306)
        float mult_const = 126.0 / (range - 1.0);
    #elif(DISPLAY_TYPE == ST_7735)
        float mult_const = 158.0 / (range - 1.0);
    #endif
    float x_pos = 0.0;

    for(int i = 0; i < FRAME_POINT_COUNT; i++) {
        x_pos = (((frames[current_frame_idx][i].x / 10.0) - offset) - 1.0) * mult_const;
        if(x_pos > CANVAS_WIDTH || x_pos < 2) continue;

        if(inspecting && x_pos < inspect + 3 && x_pos > inspect - 3 ) {
            inspect_x = frames[current_frame_idx][i].x / 10.0;
            inspect_y = frames[current_frame_idx][i].y;
        }

        display->drawFastVLine(x_pos+1, 
                               CANVAS_HEIGHT - frames[current_frame_idx][i].y,
                               frames[current_frame_idx][i].y,
                               _WHITE);
    }
}

void UTGraph::exportToSerial() {
    // CSV output
    // for(int i = 0; i < FRAME_STORAGE_COUNT; i++) {
    //     Serial.println("*==============================*");
    //     Serial.print("          FRAME ");
    //     Serial.println(i);
    //     Serial.println("*==============================*\n\n");
    //     for(int j = 0; j < FRAME_POINT_COUNT; j++) {
    //         Serial.print(frames[i][j].x);
    //         Serial.print(", ");
    //         Serial.println(frames[i][j].y);
    //     }
    //     Serial.println("*==============================*\n\n\n");
    //             Serial.println("-------------------------------------------------------------------------");
    // }

    //Python output for matplotlib

    Serial.print("\n\nx_space = [");
    for(int i = 0; i < FRAME_STORAGE_COUNT; i++) {
        Serial.print("[");
        for(int j = 0; j < FRAME_POINT_COUNT; j++) {
            Serial.print(frames[i][j].x);
            if(j != FRAME_POINT_COUNT - 1)
                Serial.print(", ");
            if(j % 50 == 0) 
                Serial.println();
        }
        if(i != FRAME_STORAGE_COUNT - 1)
            Serial.print("],");
        else 
            Serial.print("]");
    }
    Serial.println("]\n");

    Serial.print("y_space = [");
    for(int i = 0; i < FRAME_STORAGE_COUNT; i++) {
        Serial.print("[");
        for(int j = 0; j < FRAME_POINT_COUNT; j++) {
            Serial.print(frames[i][j].y);
            if(j != FRAME_POINT_COUNT - 1)
                Serial.print(", ");
            if(j % 50 == 0) 
                Serial.println();
        }
        if(i != FRAME_STORAGE_COUNT - 1)
            Serial.print("],");
        else 
            Serial.print("]");
    }
    Serial.println("]");
}

void UTGraph::runDemo() {
    delay(100);
    Serial.println("Starting demo mode...");
    running = true;
    active = true;
    XYPos_t demo_frames[FRAME_POINT_COUNT];

    drawParameterTray();
    ping->startReading();

    // Mocks UTPing's functionality
    while(running) {
        #if (DEBUGGING_MODE == true)
            //unsigned long start_millis = millis();
        #endif

        for(int i = 0; i < FRAME_POINT_COUNT; i += 1) {
            //experiment with this delay to determine max time to 
            //gather data from transducer
            //delay(100);
            demo_frames[i].x = i*10.0;
            demo_frames[i].y = uint16_t(exp(-(i/50.0))*(sin(i) + 1.0) * 20.0) * gain + random(2);//(uint16_t)((sin(i) + 1) * (gain * 10) + random(2));
        }
        delay(10);

        #if(DEBUGGING_MODE == true)
            //unsigned long frame_gen_time = millis() - start_millis;
            //Serial.print("Time to generate one frame: ");
            //Serial.print(frame_gen_time);
            //Serial.println("ms");
        #endif

        //ping->readSignal(demo_frames);
        nextFrame(demo_frames);
    }

    ping->stopReading();
}

//not finished
XYPos_t UTGraph::getCursorPositionLocation() {
    XYPos_t ret = {1, 1};
    return ret;
}

//not finished
XYPos_t UTGraph::getPositionXY(uint8_t position) {
    return {1, 1};
}

void UTGraph::changeCursorPosition(uint8_t position) {}

boolean UTGraph::isActive() {
    return active;
}

boolean UTGraph::isRunning() {
    return running || inspecting;
}

/*
 * 
 * 
 *      Private Functions
 * 
 * 
 * */

void UTGraph::setCursor(XYPos_t position) {}

//refactor this
void UTGraph::checkButtonsWhileRunning() {
    int input = digitalRead(RIGHT_PIN);
    if(input == LOW) {
        stop();
    }

    input = digitalRead(UP_PIN);
    if(input == LOW) {
        inspecting = !inspecting;
        delay(100);
    }
}

void UTGraph::checkPots() {
    int gain_val = analogRead(GAIN_PIN);
    int range_val = analogRead(RANGE_PIN);
    int offset_val = analogRead(OFFSET_PIN);
    int inspect_val = analogRead(INSPECT_PIN);

    float new_gain = (gain_val - 1.0) * analog_common_factor * adjustment_parameters->_gain;
    float new_range = (1.0 - ((range_val - 1.0) * analog_common_factor)) * adjustment_parameters->_range;
    float new_offset = (offset_val - 1.0) * analog_common_factor *  ((adjustment_parameters->_range - new_range)*100);
    #if(DISPLAY_TYPE == SSD_1306)
        float new_inspect = (inspect_val - 1.0) * analog_common_factor * 124 + 2;
    #elif(DISPLAY_TYPE == ST_7735)
        float new_inspect = (inspect_val - 1.0) * analog_common_factor * 156 + 2;
    #endif

    gain = new_gain < 0.0 ? 0.0 : new_gain; 
    range = new_range * 100; //use centimeters here
    offset = new_offset < 0 ? 0.0 : new_offset;
    inspect = new_inspect;
}

view_t UTGraph::leftPress() {return NONE;}

view_t UTGraph::rightPress() {return NONE;}

view_t UTGraph::upPress() {return NONE;}

view_t UTGraph::downPress() {return NONE;}

view_t UTGraph::enterPress() {
    return NONE;
}

void UTGraph::drawBoundaries() {
    display->drawFastVLine(canvas_data[0].y, canvas_data[0].x, canvas_data[1].y, _WHITE);
    display->drawFastHLine(canvas_data[0].y, canvas_data[1].y, canvas_data[1].x, _WHITE);
}

void UTGraph::clearGraph() {
    display->fillRect(canvas_data[0].x, canvas_data[0].y, 
                      canvas_data[1].x, canvas_data[1].y, _BLACK); //clear old data
}

//update this for the new display and make it more generic
void UTGraph::drawParameterTray() {
    #if(DISPLAY_TYPE == SSD_1306)
        display->fillRect(1, 53, 126, 10, _BLACK);
        display->drawFastVLine(38, 50, 14, _WHITE);
        display->drawFastVLine(83, 50, 14, _WHITE);
    #elif(DISPLAY_TYPE == ST_7735)
        display->drawFastHLine(0, 82, 160, _WHITE);
        display->setTextColor(_YELLOW);

        //draw top line parameter names
        display->setCursor(1, distance_position.y);
        display->print("Distance:");

        display->setCursor(102, magnitude_position.y);
        display->print("Mag:");

        display->setTextColor(_MAGENTA);

        //draw bottom parameter names
        display->setCursor(1, gain_position.y);
        display->print("Gain:");

        display->setCursor(1, range_position.y);
        display->print("Window width:");

        display->setCursor(1, offset_position.y);
        display->print("X offset:");

        display->drawFastHLine(0, 112, 160, _WHITE);
    #endif
}

//update this for the new display
#if(DISPLAY_TYPE == SSD_1306)
    void UTGraph::drawParameters() {
        char print_val[MEASURMENT_VALUE_LENGTH + 1];

        display->setCursor(gain_position.x, gain_position.y);
        display->setTextColor(_WHITE, _BLACK);
        sprintf(print_val, "%4.2fdB", gain);
        display->println(print_val);
        
        /**
         * The bottom two right parameters are 
         * different based on the mode
         * */

        display->setCursor(distance_range_position.x, distance_range_position.y);
        if(inspecting) {
            formatDisplayStringMetric(print_val, inspect_x);
            display->println(print_val);
        } else {
            formatDisplayStringMetric(print_val, range);
            display->println(print_val);
        }

        display->setCursor(magnitude_offset_position.x, magnitude_offset_position.y);
        if(inspecting) {
            sprintf(print_val, "%7.2f", inspect_y);
            display->println(print_val);
        } else {
            formatDisplayStringMetric(print_val, offset);
            display->println(print_val);
        }
    }
#elif(DISPLAY_TYPE == ST_7735)
    void UTGraph::drawParameters() {
        char print_val[MEASURMENT_VALUE_LENGTH + 1];

        display->setCursor(gain_position.x, gain_position.y);
        display->setTextColor(_WHITE, _BLACK);
        sprintf(print_val, "%5.2fdB", gain);
        display->println(print_val);
        
        /**
         * The bottom two right parameters are 
         * different based on the mode
         * */

        if(inspecting) {
            display->setCursor(distance_position.x, distance_position.y);
            formatDisplayStringMetric(print_val, inspect_x);
            display->println(print_val);
        }
        display->setCursor(range_position.x, range_position.y);
        formatDisplayStringMetric(print_val, range);
        display->println(print_val);

        if(inspecting) {
            display->setCursor(magnitude_position.x, magnitude_position.y);
            sprintf(print_val, "%5.1f", inspect_y);
            display->println(print_val);
        }
        display->setCursor(offset_position.x, offset_position.y);
        formatDisplayStringMetric(print_val, offset);
        display->println(print_val);
    }
#endif

void UTGraph::drawInspectionPointer() {
    display->fillTriangle(inspect, 5, inspect - 2, 1, inspect + 2, 1, _YELLOW);
}

//helper function
void UTGraph::formatDisplayStringMetric(char * buffer, float value_cm) {
    if(value_cm > 99) {
        value_cm /= 100.0;
        sprintf(buffer, "%5.2fm ", value_cm);
    } else {
        sprintf(buffer, "%5.2fcm", value_cm);
    }
}