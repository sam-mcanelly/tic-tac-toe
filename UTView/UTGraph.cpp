/****************************************
 * 
 * Ultrasonic Flaw Detector - UTGraph
 * Author(s): Sam McAnelly, 
 * Oklahoma State University
 * ECEN 4013
 * 
 ****************************************/

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
    Serial.println("drawing parameters...");
    //drawParameters();
    //renderCurrentFrame();

    if(show)
        display->display();
}

void UTGraph::update() {
    renderCurrentFrame();
}

void UTGraph::stop() {
    running = false;
}

void UTGraph::nextFrame(XYPos_t values[100]) {
    current_frame_idx += 1;
    if(current_frame_idx > 9) current_frame_idx = 0;

    for(int i = 0; i < 126; i++) {
        frames[current_frame_idx][i] = values[i];
    }

    renderCurrentFrame();
    clearParameterTray();
    drawParameters();
}

void UTGraph::renderCurrentFrame() {
    display->fillRect(2, 0, 128, 49, BLACK); //clear old data
    double mult_const = 126.0 / (range - 1.0);

    for(int i = 0; i < 126; i++) {
        double x_pos = ((frames[current_frame_idx][i].x - offset) - 1.0) * mult_const;
        if(x_pos > 124 || x_pos < 1) continue;
        display->drawFastVLine(x_pos+1, 51 - frames[current_frame_idx][i].y, frames[current_frame_idx][i].y, WHITE);
    }

    display->display();
}

void UTGraph::runDemo() {
    delay(100);
    running = true;
    XYPos_t demo_frames[126];

    while(running) {
        for(double i = 0; i < 126.0; i += 1.0) {
            demo_frames[(int)i].x = i / 4;
            demo_frames[(int)i].y = (exp(-1.0*(i/20))*(sin(i) + 1) * 50.0) * gain + random(2);//random(i/2) * gain;
        }

        nextFrame(demo_frames);
        
        delay(10);
        checkButtons();
        checkPots();
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
    return running;
}

/*
 * 
 * 
 *      Private Functions
 * 
 * 
 * */

void UTGraph::setCursor(XYPos_t position) {}

void UTGraph::checkButtons() {
    Serial.println("Checking buttons...");

    int input = digitalRead(ENTER_PIN);
    if(input == LOW) {
        delay(200);
        if(input == LOW){
            running = false;
        }
    }
}

void UTGraph::checkPots() {
    int gain_val = analogRead(GAIN_PIN);
    int range_val = analogRead(RANGE_PIN);
    int offset_val = analogRead(OFFSET_PIN);

    double common_factor = 1 / (1023.0 - 1.0);

    double new_gain = (gain_val - 1.0) * common_factor * adjustment_parameters->_gain;
    double new_range = (1.0 - ((range_val - 1.0) * common_factor)) * adjustment_parameters->_range;
    double new_offset = (offset_val - 1.0) * common_factor *  ((adjustment_parameters->_range - new_range)*100);
  
    gain = new_gain; 
    range = new_range * 100; //use centimeters here
    offset = new_offset < 0 ? 0.0 : new_offset;
}

view_t UTGraph::leftPress() {return NONE;}

view_t UTGraph::rightPress() {return NONE;}

view_t UTGraph::upPress() {return NONE;}

view_t UTGraph::downPress() {return NONE;}

view_t UTGraph::enterPress() {
    //if(isRunning()) running = false;

    return NONE;}

void UTGraph::drawBoundaries() {
    display->drawFastVLine(1, 1, 50, WHITE);
    display->drawFastHLine(1, 50, 127, WHITE);
}

void UTGraph::clearParameterTray() {
    display->fillRect(1, 54, 127, 10, BLACK);
}

void UTGraph::drawParameters() {
    String gain_s = String(gain) + "dB";
    String range_s = String(range/100) + "m";
    String offset_s = String(offset/100) + "m";

    display->setCursor(1, 54);
    display->setTextColor(WHITE, BLACK);
    display->println(gain_s);

    
    display->setCursor(50, 54);
    display->println(range_s);

    display->setCursor(95, 54);
    display->println(offset_s);
}