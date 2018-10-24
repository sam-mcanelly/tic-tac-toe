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
    return mainInputPositions[input_cursor_position];
}

XYPos_t UTMain::getPositionXY(uint8_t position) {
    return mainInputPositions[position];
}

void UTMain::changeCursorPosition(uint8_t new_position) {
    //check bounds
    if(new_position == MAIN_IO_COUNT) new_position = 0;
    else if(new_position < 0) new_position = MAIN_IO_COUNT - 1;

    //unselect previous button
    #if(DISPLAY_TYPE == SSD_1306)
        display->setCursor(mainInputPositions[input_cursor_position].x, mainInputPositions[input_cursor_position].y);
        display->setTextColor(_WHITE, _BLACK);
        display->println(mainViewStrings[input_cursor_position]);
    #elif(DISPLAY_TYPE == ST_7735)
        display->deselectButton(mainInputPositions[input_cursor_position].x,
                            mainInputPositions[input_cursor_position].y,
                            mainViewStrings[input_cursor_position],
                            SMALL);
    #endif
    input_cursor_position = new_position;
    setCursor(getCursorPositionLocation());
    display->display();
}

view_t UTMain::buttonPress(input_t i) {
    //if(graph->isActive()) return;

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
    #if(DISPLAY_TYPE == SSD_1306)
        //sets cursor to draw, not input cursor
        display->setCursor(position.x, position.y);

        display->setTextColor(_BLACK, _WHITE);
        display->println(mainViewStrings[input_cursor_position]);
    #elif(DISPLAY_TYPE == ST_7735)
        display->selectButton(position.x, position.y, mainViewStrings[input_cursor_position], SMALL);
    #endif
}

view_t UTMain::leftPress() {
    if(input_cursor_position == 0)
        changeCursorPosition(MAIN_IO_COUNT - 1);
    else
        changeCursorPosition(input_cursor_position - 1);

    return NONE;
}

view_t UTMain::rightPress() {
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

        //This one is really weird...
        //The interrupt gets re-mapped to the right button
        //when the graph is running.
        //right exits the graph
        case 1: //start
            if(!graph->isActive()) {
                graph->runDemo();
            } else {
                graph->exit();
                #if(DISPLAY_TYPE == SSD_1306)
                    display->fillRect(0, 51, 128, 13, _BLACK);
                #elif(DISPLAY_TYPE == ST_7735)

                #endif
                drawMainViewButtons();

                //this handles the double enter/right press bug
                input_cursor_position -= 1;
            }
            break;
        case 2: //export
            graph->exportToSerial();
            break;
    }

    return NONE;
}

void UTMain::drawMainViewButtons() {
    #if(DISPLAY_TYPE == SSD_1306)
        //draw borders
        display->drawFastVLine(127, 50, 14, _WHITE);
        display->drawFastVLine(0, 50, 14, _WHITE);
        display->drawFastHLine(0, 63, CANVAS_WIDTH, _WHITE);

        display->setTextColor(_WHITE, _BLACK);

        for(uint8_t i = 0; i < MAIN_IO_COUNT; i++) {
            display->setCursor(mainInputPositions[i].x, mainInputPositions[i].y);
            display->println(mainViewStrings[i]);
        }
    #elif(DISPLAY_TYPE == ST_7735)
        for(uint8_t i = 0; i < MAIN_IO_COUNT; i++) {
            display->drawButton(mainInputPositions[i].x, mainInputPositions[i].y, mainViewStrings[i], SMALL);
        }
    #endif
}