/****************************************
 * 
 * Ultrasonic Flaw Detector - UTMain
 * Author(s): Sam McAnelly, 
 * Oklahoma State University
 * ECEN 4013
 * 
 ****************************************/

#include "UTMain.h"

/*
 * 
 * 
 *      Public Functions
 * 
 * 
 * */

void UTMain::create() {
    graph->create();
    drawMainViewButtons();
    changeCursorPosition(input_cursor_position);
    display->display();
}

XYPos_t UTMain::getCursorPositionLocation() {
    if(!graphActive) {
        return mainInputPositions[input_cursor_position];
    } else {

    }
}

XYPos_t UTMain::getPositionXY(uint8_t position) {
    if(!graphActive) {
        return mainInputPositions[position];
    } else {

    }
}

void UTMain::changeCursorPosition(uint8_t new_position) {
    if(new_position == MAIN_IO_COUNT) new_position = 0;
    else if(new_position < 0) new_position = MAIN_IO_COUNT - 1;

    display->setCursor(mainInputPositions[input_cursor_position].x, mainInputPositions[input_cursor_position].y);
    display->setTextColor(WHITE, BLACK);
    display->println(mainViewStrings[input_cursor_position]);
    input_cursor_position = new_position;
    setCursor(getCursorPositionLocation());
}

void UTMain::buttonPress(_input i) {
    if(graphActive) return graph->buttonPress(i);
    switch(i) {
        case 0:
            return upPress();
        case 1:
            return downPress();
        case 2:
            return leftPress();
        case 3:
            return rightPress();
        case 4:
            return enterPress();
    }  
}

/*
 * 
 * 
 *      Private Functions
 * 
 * 
 * */

void UTMain::setCursor(XYPos_t position) {
    //sets cursor to draw, not input cursor
    display->setCursor(position.x, position.y);
    display->setTextColor(BLACK, WHITE);
    display->println(mainViewStrings[input_cursor_position]);
}

void UTMain::leftPress() {
    changeCursorPosition(--input_cursor_position);
}

void UTMain::rightPress() {
    changeCursorPosition(++input_cursor_position);
}

void UTMain::upPress() {
}

void UTMain::downPress() {
}

void UTMain::enterPress() {
    switch(input_cursor_position) {
        case 0: //menu
            //switchView(MENU, 0);
            break;
        case 1: //start
            break;
        case 2: //pause
            break;
    }
}

void UTMain::drawMainViewButtons() 
{
    uint8_t menuPos = 0;

    display->setTextColor(WHITE, BLACK);

    for(uint8_t i = 0; i < MAIN_IO_COUNT; i++) {
        display->setCursor(mainInputPositions[i].x, mainInputPositions[i].y);
        display->println(mainViewStrings[i]);
    }
}