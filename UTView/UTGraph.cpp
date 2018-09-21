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
    display->drawFastVLine(1, 1, 50, WHITE);
    display->drawFastHLine(1, 50, 125, WHITE);
    
    if(show)
        display->display();
}

XYPos_t UTGraph::getCursorPositionLocation() {
    XYPos_t ret = {1, 1};
    return ret;
}

XYPos_t UTGraph::getPositionXY(uint8_t position) {
    return {1, 1};
}

void UTGraph::changeCursorPosition(uint8_t position) {}

/*
 * 
 * 
 *      Private Functions
 * 
 * 
 * */

void UTGraph::setCursor(XYPos_t position) {}

view_t UTGraph::leftPress() {return NONE;}

view_t UTGraph::rightPress() {return NONE;}

view_t UTGraph::upPress() {return NONE;}

view_t UTGraph::downPress() {return NONE;}

view_t UTGraph::enterPress() {return NONE;}