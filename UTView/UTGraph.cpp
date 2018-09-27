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

    if(show)
        display->display();
}

void UTGraph::update() {
    renderCurrentFrame();
}

void UTGraph::stop() {
    inspecting = false;
    running = false;
}

void UTGraph::nextFrame(XYPos_t values[100]) {
    current_frame_idx += 1;
    if(current_frame_idx > 9) current_frame_idx = 0;

    for(int i = 0; i < 126; i++) {
        frames[current_frame_idx][i] = values[i];
    }

    checkButtonsWhileRunning();

    renderCurrentFrame();
    checkPots();
    clearParameterTray();
    drawParameters();

    display->display();
}

void UTGraph::renderCurrentFrame() {
    display->fillRect(1, 0, 128, 49, BLACK); //clear old data
    double mult_const = 126.0 / (range - 1.0);

    for(int i = 0; i < 126; i++) {
        double x_pos = ((frames[current_frame_idx][i].x - offset) - 1.0) * mult_const;
        if(x_pos > 124 || x_pos < 2) continue;
        if(inspecting && x_pos < inspect + 3 && x_pos > inspect - 3 ) {
            inspect_x = frames[current_frame_idx][i].x;
            inspect_y = frames[current_frame_idx][i].y;
        }

        //currentWindow.push_back(frames[current_frame_idx][i]);
        display->drawFastVLine(x_pos+1, 51 - frames[current_frame_idx][i].y, frames[current_frame_idx][i].y, WHITE);
    }
}

void UTGraph::exportToSerial() {
    for(int i = 0; i < 10; i++) {
        Serial.println("*==============================*");
        Serial.print("          FRAME ");
        Serial.println(i);
        Serial.println("*==============================*\n\n");
        for(int j = 0; j < 126; j++) {
            Serial.print(frames[i][j].x);
            Serial.print(", ");
            Serial.println(frames[i][j].y);
        }
        Serial.println("*==============================*\n\n\n");
                Serial.println("-------------------------------------------------------------------------");
    }
}

void UTGraph::runDemo() {
    delay(100);
    running = true;
    XYPos_t demo_frames[126];

    while(running) {
        for(double i = 0; i < 126.0; i += 1.0) {
            demo_frames[(int)i].x = i / 16;
            demo_frames[(int)i].y = (exp(-1.0*(i/20))*(sin(i) + 1) * 50.0) * gain + random(5);//random(i/2) * gain;
        }

        nextFrame(demo_frames);
    }
    clearParameterTray();
}

XYPos_t UTGraph::getCursorPositionLocation() {
    XYPos_t ret = {1, 1};
    return ret;
}

XYPos_t UTGraph::getPositionXY(uint8_t position) {
    return {1, 1};
}

void UTGraph::changeCursorPosition(uint8_t position) {}

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

void UTGraph::checkButtonsWhileRunning() {
    int input = digitalRead(ENTER_PIN);
    if(input == LOW) {
        delay(100);
        if(input == LOW){
            stop();
        }
    }

    input = digitalRead(UP_PIN);
    if(input == LOW) {
        delay(100);
        if(input == LOW) {
            inspecting = !inspecting;
        }
    }
}

void UTGraph::checkPots() {
    int gain_val = analogRead(GAIN_PIN);
    int range_val = analogRead(RANGE_PIN);
    int offset_val = analogRead(OFFSET_PIN);
    int inspect_val = analogRead(INSPECT_PIN);

    double common_factor = 1 / (1023.0 - 1.0);

    double new_gain = (gain_val - 1.0) * common_factor * adjustment_parameters->_gain;
    double new_range = (1.0 - ((range_val - 1.0) * common_factor)) * adjustment_parameters->_range;
    double new_offset = (offset_val - 1.0) * common_factor *  ((adjustment_parameters->_range - new_range)*100);
    double new_inspect = (inspect_val - 1.0) * common_factor * 124 + 2;

    gain = new_gain; 
    range = new_range * 100; //use centimeters here
    offset = new_offset < 0 ? 0.0 : new_offset;
    inspect = new_inspect;
}

view_t UTGraph::leftPress() {return NONE;}

view_t UTGraph::rightPress() {return NONE;}

view_t UTGraph::upPress() {return NONE;}

view_t UTGraph::downPress() {return NONE;}

view_t UTGraph::enterPress() {
    //if(isRunning()) running = false;

    return NONE;
}

void UTGraph::drawBoundaries() {
    display->drawFastVLine(0, 1, 50, WHITE);
    display->drawFastHLine(0, 50, 127, WHITE);
}

void UTGraph::clearGraph() {
    display->fillRect(canvas_data[0].x, canvas_data[0].y, 
                      canvas_data[1].x, canvas_data[1].y, BLACK); //clear old data
}

void UTGraph::clearParameterTray() {
    display->fillRect(1, 54, 127, 10, BLACK);
}

void UTGraph::drawParameters() {
    String gain_s = String(gain) + decibal;
    String range_s = String(range) + centimeters;
    String offset_s = String(offset) + centimeters;

    display->setCursor(gain_position.x, gain_position.y);
    display->setTextColor(WHITE, BLACK);
    display->println(gain_s);
    
    /**
     * The bottom two right parameters are 
     * different based on the mode
     * */

    display->setCursor(distance_range_position.x, distance_range_position.y);
    if(inspecting) {
        display->print(inspect_x);
        display->println(centimeters);
        drawInspectionPointer();
    } else {
        display->println(range_s);
    }

    display->setCursor(magnitude_offset_position.x, magnitude_offset_position.y);
    if(inspecting) {
        display->println(inspect_y);
    } else {
        display->println(offset_s);
    }
}

void UTGraph::drawInspectionPointer() {
    display->fillTriangle(inspect, 5, inspect - 2, 1, inspect + 2, 1, WHITE);
}