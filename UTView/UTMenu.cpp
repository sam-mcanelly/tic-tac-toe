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

    //unselect old position
    display->setCursor(menuInputPositions[input_cursor_position].x, menuInputPositions[input_cursor_position].y);

    //display specific color settings
    #if(DISPLAY_TYPE == SSD_1306)
        display->setTextColor(_WHITE, _BLACK);
    #elif(DISPLAY_TYPE == ST_7735)
        display->setTextColor(_BLACK, _WHITE);
    #endif
    
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

    //display specific color settings
    #if(DISPLAY_TYPE == SSD_1306)
        display->setTextColor(_BLACK, _WHITE);
    #elif(DISPLAY_TYPE == ST_7735)
        display->setTextColor(_WHITE, _BLACK);
    #endif

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
    #if(DISPLAY_TYPE == SSD_1306)
        display->fillRect(0, 10, 70, 42, _BLACK);
        display->drawRect(0, 10, 70, 42, _WHITE);
    #elif(DISPLAY_TYPE == ST_7735)
        display->setCursor(45, 5);
        display->setTextColor(_RED, _BLACK);
        display->print("Settings");
        display->fillRect(45, 15, 70, 42, _WHITE);
        display->drawRect(45, 15, 70, 42, _RED);
    #endif 
}


void UTMenu::drawMenuButtons() {
    #if(DISPLAY_TYPE == SSD_1306)
        display->setTextColor(_WHITE, _BLACK);
    #elif(DISPLAY_TYPE == ST_7735)
        display->setTextColor(_BLACK);
    #endif
    
    for(uint8_t i = 0; i < MENU_IO_COUNT; i++) {
        display->setCursor(menuInputPositions[i].x, menuInputPositions[i].y);
        display->println(menuViewStrings[i]);
    }
}