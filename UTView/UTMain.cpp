#include "UTMain.h"

void UTMain::create() {
    graph->create();
    drawMainViewButtons();
    changeCursorPosition(input_cursor_position);
    display->display();
}

void UTMain::changeCursorPosition(uint8_t new_position) {
    display->setCursor(mainInputPositions[input_cursor_position].x, mainInputPositions[input_cursor_position].y);
    display->setTextColor(WHITE, BLACK);
    display->println(mainViewStrings[input_cursor_position]);
    input_cursor_position = new_position;
    setCursor(getCursorPositionLocation());
}

void UTMain::setCursor(XYPos_t position) {
    //sets cursor to draw, not input cursor
    display->setCursor(position.x, position.y);
    display->setTextColor(BLACK, WHITE);
    display->println(mainViewStrings[input_cursor_position]);
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

void UTMain::moveInputCursor(_input i)
{
    switch(i)
    {
        case UP:
            break;
        case DOWN: 
            break;
        case LEFT: 
            //set the old one to the non-selected mode
            setCursor(mainInputPositions[input_cursor_position]);
            display->setTextColor(WHITE, BLACK);
            display->println(mainViewStrings[input_cursor_position]);

            //update the newly selected position
            input_cursor_position -= 1;
            if(input_cursor_position < 0) input_cursor_position = MAIN_IO_COUNT - 1;
            setCursor(mainInputPositions[input_cursor_position]);
            display->setTextColor(BLACK, WHITE);
            display->println(mainViewStrings[input_cursor_position]);
            break;
        case RIGHT:
            //set the old one to the non-selected mode
            setCursor(mainInputPositions[input_cursor_position]);
            display->setTextColor(WHITE, BLACK);
            display->println(mainViewStrings[input_cursor_position]);

            //update the newly selected position
            input_cursor_position = (input_cursor_position + 1) % MAIN_IO_COUNT; 
            setCursor(mainInputPositions[input_cursor_position]);
            display->setTextColor(BLACK, WHITE);
            display->println(mainViewStrings[input_cursor_position]);
            break;
    }

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

void UTMain::leftPress() {
    moveInputCursor(LEFT);
}

void UTMain::rightPress() {
    moveInputCursor(LEFT);
}

void UTMain::upPress() {
    moveInputCursor(LEFT);
}

void UTMain::downPress() {
    moveInputCursor(LEFT);
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