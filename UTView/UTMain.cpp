#include "UTMain.h"

void UTMain::create() {
    graph->create();
    drawMainViewButtons();
    display->display();
}

void UTMain::drawMainViewButtons() 
{
    uint8_t menuPos = 0;

    setCursor(menuPosition);
    display->setTextColor(BLACK, WHITE);
    display->println(mainViewStrings[menuPos++]);
    
    setCursor(startPosition);
    display->setTextColor(WHITE, BLACK);
    display->println(mainViewStrings[menuPos++]);

    setCursor(pausePosition);
    display->println(mainViewStrings[menuPos++]);
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
            setCursor(mainInputPositions[inputCursorPosition]);
            display->setTextColor(WHITE, BLACK);
            display->println(mainViewStrings[inputCursorPosition]);

            //update the newly selected position
            inputCursorPosition -= 1;
            if(inputCursorPosition < 0) inputCursorPosition = MAIN_IO_COUNT - 1;
            setCursor(mainInputPositions[inputCursorPosition]);
            display->setTextColor(BLACK, WHITE);
            display->println(mainViewStrings[inputCursorPosition]);
            break;
        case RIGHT:
            //set the old one to the non-selected mode
            setCursor(mainInputPositions[inputCursorPosition]);
            display->setTextColor(WHITE, BLACK);
            display->println(mainViewStrings[inputCursorPosition]);

            //update the newly selected position
            inputCursorPosition = (inputCursorPosition + 1) % MAIN_IO_COUNT; 
            setCursor(mainInputPositions[inputCursorPosition]);
            display->setTextColor(BLACK, WHITE);
            display->println(mainViewStrings[inputCursorPosition]);
            break;
    }

    display->display();
}

XYPos_t UTMain::getCursorPositionLocation() {
    if(!graphActive) {
        return mainInputPositions[inputCursorPosition];
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
    switch(inputCursorPosition) {
        case 0: //menu
            //switchView(MENU, 0);
            break;
        case 1: //start
            break;
        case 2: //pause
            break;
    }
}