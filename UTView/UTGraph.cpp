#include "UTGraph.h"

void UTGraph::create() {
    display->drawFastVLine(1, 1, 50, WHITE);
    display->drawFastHLine(1, 50, 125, WHITE);
    display->display();
}

XYPos_t UTGraph::getCursorPositionLocation() {
    XYPos_t ret = {1, 1};
    return ret;
}

XYPos_t UTGraph::getPositionXY(uint8_t position) {
    return {1, 1};
}

void UTGraph::changeCursorPosition(uint8_t position) {

}

void UTGraph::setCursor(XYPos_t position) {

}

/*
 * 
 * 
 *      Private Functions
 * 
 * 
 * */

void UTGraph::moveInputCursor(_input i) {

}

void UTGraph::leftPress() {

}

void UTGraph::rightPress() {
    
}

void UTGraph::upPress() {
    
}

void UTGraph::downPress() {
    
}

void UTGraph::enterPress() {
    
}