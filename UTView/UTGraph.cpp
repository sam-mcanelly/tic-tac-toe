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

void UTGraph::renderCurrentFrame() {
    display->fillRect(2, 1, 101, 49, BLACK); //clear old data

    for(int i = 0; i < 100; i++) {
        display->drawFastVLine(i+2, 50 - frames[0][i], frames[0][i], WHITE);
    }

    display->display();
}

void UTGraph::runDemo() {
    delay(100);
    running = true;
    Serial.println("Running demo...");

    while(running) {
        for(int i = 0; i < 100; i++) {
            frames[0][i] = random(i/2);
        }

        renderCurrentFrame();
        delay(20);
        checkButtons();
    }
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
        Serial.println("Stopping graph!");
        delay(400);
        if(input == LOW)
            running = false;
    }
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
    display->drawFastHLine(1, 50, 101, WHITE);
}