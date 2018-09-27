/****************************************
 * 
 * Ultrasonic Flaw Detector - UTMenu
 * Author(s): Sam McAnelly, 
 * Oklahoma State University
 * ECEN 4013
 * 
 ****************************************/

#include "UTMenu.h"

/*
 * 
 * 
 *      Public Functions
 * 
 * 
 * */

void UTMenu::create(boolean show) {
    drawMenuContainer();
    drawMenuButtons();
    changeCursorPosition(input_cursor_position);

    if(show)
        display->display();
}

XYPos_t UTMenu::getCursorPositionLocation() {
    return menuInputPositions[input_cursor_position];
}

XYPos_t UTMenu::getPositionXY(uint8_t position) {
    return menuInputPositions[position];
}

void UTMenu::changeCursorPosition(uint8_t new_position) {
    //check bounds
    if(new_position == MENU_IO_COUNT) new_position = 0;
    else if(new_position < 0) new_position = MENU_IO_COUNT - 1;

    display->setCursor(menuInputPositions[input_cursor_position].x, menuInputPositions[input_cursor_position].y);
    display->setTextColor(WHITE, BLACK);
    display->println(menuViewStrings[input_cursor_position]);
    input_cursor_position = new_position;
    setCursor(menuInputPositions[input_cursor_position]);
    display->display();
}

/*
 * 
 * 
 *      Private Functions
 * 
 * 
 * */

void UTMenu::setCursor(XYPos_t position) {
    //sets cursor to draw, not input cursor
    display->setCursor(position.x, position.y);
    display->setTextColor(BLACK, WHITE);
    display->println(menuViewStrings[input_cursor_position]);
}

view_t UTMenu::leftPress() {return BACK;}

view_t UTMenu::rightPress() {return NONE;}

view_t UTMenu::upPress() {
    if(input_cursor_position == 0)
        changeCursorPosition(MENU_IO_COUNT - 1);
    else
        changeCursorPosition(input_cursor_position - 1);
    
    return NONE;
}

view_t UTMenu::downPress() {
    changeCursorPosition(input_cursor_position + 1);
    return NONE;
}

view_t UTMenu::enterPress() {
    switch(input_cursor_position) {
        case 0: 
            return DELAY;
        case 1: 
            return GAIN;
        case 2: 
            return RANGE;
        case 3:
            return CALIBRATE;
    }

    return NONE;
}

void UTMenu::drawMenuContainer() {
    //create border for menu
    display->fillRect(0, 10, 70, 42, BLACK);
    display->drawRect(0, 10, 70, 42, WHITE); 
}


void UTMenu::drawMenuButtons() {
    display->setTextColor(WHITE, BLACK);
    
    for(uint8_t i = 0; i < MENU_IO_COUNT; i++) {
        display->setCursor(menuInputPositions[i].x, menuInputPositions[i].y);
        display->println(menuViewStrings[i]);
    }
}