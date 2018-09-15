/****************************************
 * 
 * Ultrasonic Flaw Detector - UTView
 * Author(s): Sam McAnelly, 
 * Oklahoma State University
 * ECEN 4013
 * 
 ****************************************/

#include "UTView.h"

Adafruit_SSD1306 display(OLED_RESET);

void UTView::begin() {
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    showSplashScreen();
    
    running = false;

    graph = new UTGraph(&display);
    main = new UTMain(&display, graph);

    active_component = main;
    main->create();
}

bool UTView::isRunning() {
    return running;
}

void UTView::handlePress(_input i) {
    active_component->buttonPress(i);
}

void UTView::showSplashScreen() {
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






