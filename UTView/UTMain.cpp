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

void UTMain::create(boolean show) {
    graph->create(show);
    drawMainViewButtons();
    changeCursorPosition(input_cursor_position);

    if(show)
        display->display();
}

void UTMain::showGraph() {
    graph->renderCurrentFrame();
}

XYPos_t UTMain::getCursorPositionLocation() {
    if(!graphActive) {
        return mainInputPositions[input_cursor_position];
    } else {
        return {0, 0};
    }
}

XYPos_t UTMain::getPositionXY(uint8_t position) {
    if(!graphActive) {
        return mainInputPositions[position];
    } else {
        return {0, 0};
    }
}

void UTMain::changeCursorPosition(uint8_t new_position) {
    //Serial.println("changeCursorPosition called in Main view");
    if(new_position == MAIN_IO_COUNT) new_position = 0;
    else if(new_position < 0) new_position = MAIN_IO_COUNT - 1;

    Serial.print("new cursor position:");
    Serial.println(new_position);

    display->setCursor(mainInputPositions[input_cursor_position].x, mainInputPositions[input_cursor_position].y);
    display->setTextColor(WHITE, BLACK);
    display->println(mainViewStrings[input_cursor_position]);
    input_cursor_position = new_position;
    setCursor(getCursorPositionLocation());
    display->display();
}

view_t UTMain::buttonPress(input_t i) {
    // Serial.print("buttonPress(");
    // Serial.print(i);
    // Serial.println(") was called");
    //if(graphActive) return graph->buttonPress(i);
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
        default:
            return rightPress();
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

view_t UTMain::leftPress() {
    //Serial.println("leftPress() called in Main view");
    if(input_cursor_position == 0)
        changeCursorPosition(MAIN_IO_COUNT - 1);
    else
        changeCursorPosition(input_cursor_position - 1);

    return NONE;
}

view_t UTMain::rightPress() {
    //Serial.println("rightPress() called in Main view");
    changeCursorPosition(input_cursor_position + 1);
    return NONE;
}

view_t UTMain::upPress() {
    return NONE;
}

view_t UTMain::downPress() {
    return NONE;
}

view_t UTMain::enterPress() {
    switch(input_cursor_position) {
        case 0: //menu
            return MENU;
            break;
        case 1: //start
            changeCursorPosition(2);
            graph->runDemo();
            break;
        case 2: //pause
            graph->stop();
            break;
    }

    return NONE;
}

void UTMain::drawMainViewButtons() {
    display->setTextColor(WHITE, BLACK);

    for(uint8_t i = 0; i < MAIN_IO_COUNT; i++) {
        display->setCursor(mainInputPositions[i].x, mainInputPositions[i].y);
        display->println(mainViewStrings[i]);
    }
}