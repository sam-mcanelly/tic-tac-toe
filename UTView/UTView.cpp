#include "UTView.h"

Adafruit_SSD1306 display(OLED_RESET);

UTView::UTView()
{

}

void UTView::begin()
{
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    showSplashScreen();
    showMainView();
    running = false;
    inputCursorPosition = 0;

}

void UTView::showSplashScreen()
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(20,24);
    display.println("Ultrasonic Flaw");
    display.println("    Detector v0.1");
    display.display(); // show splashscreen
    delay(1000);
    display.startscrollleft(0x00, 0x0F);
    delay(4000);
    display.stopscroll();
    display.clearDisplay();   // clears the screen and buffer
    display.display();
}

void UTView::switchView(view newView)
{
    //don't do anything if the transducer is working
    if(running || newView == currentView) return;

    switch(newView)
    {
        case MAIN:
            showMainView();
            break;
        case MENU:
            showMenuView();
            break;
        case CALIBRATE:
            showCalibrateView();
            break;
        case GAIN:
            showGainView();
            break;
        case DELAY:
            showDelayView();
            break;
    }
}

void UTView::handlePress(uint8_t i)
{
    //this matches the mapping in the controller file
    switch(i)
    {
        case 0: 
            return upPress();
            break;
        case 1: 
            return downPress();
            break;
        case 2: 
            return leftPress();
            break;
        case 3: 
            return rightPress();
            break;
        case 4: 
            return enterPress();
            break;
    }
}

void UTView::leftPress()
{
    switch(currentView)
    {
        case MAIN:
            moveInputCursor(LEFT);
            break;
        case MENU:
            showMainView();
            break;
        case CALIBRATE:
            break;
        case DELAY:
            break;
        case GAIN:
            break;
    }
}

void UTView::rightPress()
{
    switch(currentView)
    {
        case MAIN:
            moveInputCursor(RIGHT);
            break;
        case MENU:
            break;
        case CALIBRATE:
            break;
        case DELAY:
            break;
        case GAIN:
            break;
    }
}

void UTView::upPress()
{
    switch(currentView)
    {
        case MAIN:
            break;
        case MENU:  
            moveInputCursor(UP);
            break;
        case CALIBRATE:
            break;
        case DELAY:
            break;
        case GAIN:
            break;
    }
}

void UTView::downPress()
{
    switch(currentView)
    {
        case MAIN:
            break;
        case MENU:
            moveInputCursor(DOWN);
            break;
        case CALIBRATE:
            break;
        case DELAY:
            break;
        case GAIN:
            break;      
    }
}

void UTView::enterPress()
{
    switch(currentView)
    {
        case MAIN:
            handleMainEnterPress();
            break;
        case MENU:
            break;
        case CALIBRATE:
            break;
        case DELAY:
            break;
        case GAIN:
            break;       
    }
}

void UTView::handleMainEnterPress()
{
    switch(inputCursorPosition)
    {
        case 0:
            showMenuView();
            break;
        case 1: 
            break;
        case 2:
            break;
    }
}

void UTView::showMainView()
{
    currentView = MAIN;
    display.clearDisplay();
    drawGraph();
    drawMainViewButtons();

    display.display();
}

void UTView::showMenuView()
{
    currentView = MENU;
    inputCursorPosition = 0;
    display.fillRect(0, 10, 70, 42, BLACK);
    display.drawRect(0, 10, 70, 42, WHITE);

    drawMenuViewButtons();

    display.display();
}

void UTView::drawGraph()
{
    display.drawFastVLine(1, 1, 50, WHITE);
    display.drawFastHLine(1, 50, 125, WHITE);
}

void UTView::drawMenuViewButtons()
{
    uint8_t menuPos = 0;

    setCursor(delayPosition);
    display.setTextColor(BLACK, WHITE);
    display.println(menuViewStrings[menuPos++]);

    setCursor(gainPosition);
    display.setTextColor(WHITE, BLACK);
    display.println(menuViewStrings[menuPos++]);

    setCursor(rangePosition);
    display.println(menuViewStrings[menuPos++]);
    
    setCursor(calibratePosition);
    display.println(menuViewStrings[menuPos++]);
}

void UTView::drawMainViewButtons() 
{
    uint8_t menuPos = 0;

    setCursor(menuPosition);
    display.setTextColor(BLACK, WHITE);
    display.println(mainViewStrings[menuPos++]);
    
    setCursor(startPosition);
    display.setTextColor(WHITE, BLACK);
    display.println(mainViewStrings[menuPos++]);

    setCursor(pausePosition);
    display.println(mainViewStrings[menuPos++]);
}

void UTView::setCursor(XYPos_t position)
{
    display.setCursor(position.x, position.y);
}

void UTView::moveInputCursor(_input i)
{
    switch(currentView)
    {
        case MAIN:
            moveMainCursor(i);
            break;
        case MENU:
            moveMenuCursor(i);
            break;

    }
}

void UTView::moveMainCursor(_input i)
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
            display.setTextColor(WHITE, BLACK);
            display.println(mainViewStrings[inputCursorPosition]);

            //update the newly selected position
            inputCursorPosition -= 1;
            if(inputCursorPosition < 0) inputCursorPosition = MAIN_IO_COUNT - 1;
            setCursor(mainInputPositions[inputCursorPosition]);
            display.setTextColor(BLACK, WHITE);
            display.println(mainViewStrings[inputCursorPosition]);
            break;
        case RIGHT:
            //set the old one to the non-selected mode
            setCursor(mainInputPositions[inputCursorPosition]);
            display.setTextColor(WHITE, BLACK);
            display.println(mainViewStrings[inputCursorPosition]);

            //update the newly selected position
            inputCursorPosition = (inputCursorPosition + 1) % MAIN_IO_COUNT; 
            setCursor(mainInputPositions[inputCursorPosition]);
            display.setTextColor(BLACK, WHITE);
            display.println(mainViewStrings[inputCursorPosition]);
            break;
        case ENTER: 
            break;
    }

    display.display();
}

void UTView::moveMenuCursor(_input i)
{
    switch(i)
    {
        case UP:
            //set the old one to the non-selected mode
            setCursor(menuInputPositions[inputCursorPosition]);
            display.setTextColor(WHITE, BLACK);
            display.println(menuViewStrings[inputCursorPosition]);

            //update the newly selected position
            inputCursorPosition -= 1;
            if(inputCursorPosition < 0) inputCursorPosition = MENU_IO_COUNT - 1;
            setCursor(menuInputPositions[inputCursorPosition]);
            display.setTextColor(BLACK, WHITE);
            display.println(menuViewStrings[inputCursorPosition]);
            break;
        case DOWN:
            //set the old one to the non-selected mode
            setCursor(menuInputPositions[inputCursorPosition]);
            display.setTextColor(WHITE, BLACK);
            display.println(menuViewStrings[inputCursorPosition]);

            //update the newly selected position
            inputCursorPosition = (inputCursorPosition + 1) % MENU_IO_COUNT;
            if(inputCursorPosition < 0) inputCursorPosition = MENU_IO_COUNT - 1;
            setCursor(menuInputPositions[inputCursorPosition]);
            display.setTextColor(BLACK, WHITE);
            display.println(menuViewStrings[inputCursorPosition]);
            break;
    }

    display.display();
}





