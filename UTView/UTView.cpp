#include "UTView.h"

Adafruit_SSD1306 display(OLED_RESET);

void UTView::begin()
{
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    showSplashScreen();
    
    running = false;

    main = new UTMain(&display);
    components.push(main);
}

bool UTView::isRunning()
{
    return running;
}

void UTView::handlePress(uint8_t i) {

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
    delay(8000);
    display.stopscroll();
    display.clearDisplay();   // clears the screen and buffer
    display.display();
}

void UTView::switchView(view newView, uint8_t position)
{
    //don't do anything if the transducer is working
    if(running) return;

    switch(newView)
    {
        case MAIN:
            
            break;
        case MENU:
            
            break;
        case CALIBRATE:
            
            break;
        case GAIN:
            
            break;
        case RANGE:
            
            break;
        case DELAY:
            
            break;
    }
}


// void UTView::handleMainEnterPress()
// {
//     switch(inputCursorPosition)
//     {
//         case 0: //menu
//             //add menu to stack
            
//             break;
//         case 1: //start
//             break;
//         case 2: //pause
//             break;
//     }
// }

// void UTView::handleMenuEnterPress()
// {
//     switch(inputCursorPosition)
//     {
//         case 0: //delay
            
//             break;
//         case 1: //gain
            
//             break;
//         case 2: //range
            
//             break;
//         case 3: //calibrate
            
//             break;
//     }
// }

// void UTView::handleDelayEnterPress()
// {

// }

// void UTView::handleGainEnterPress()
// {
// }

// void UTView::handleRangeEnterPress()
// {

// }

// void UTView::handleCalibrateEnterPress()
// {

// }

// void UTView::moveInputCursor(_input i)
// {
//     switch(currentView)
//     {
//         case MAIN:
//             moveMainCursor(i);
//             break;
//         case MENU:
//             moveMenuCursor(i);
//             break;

//     }
// }





