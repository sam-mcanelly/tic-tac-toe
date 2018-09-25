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
    //showSplashScreen();

    graph = new UTGraph(&display, &adjustment_parameters);
    main = new UTMain(&display, graph);
    menu = new UTMenu(&display);
    delay_adjuster = new UTAdjuster(&display,
                                    &adjustment_parameters._delay,
                                    adjustment_parameters._delay_digits,
                                    micro_seconds);
    gain_adjuster = new UTAdjuster(&display,
                                    &adjustment_parameters._gain,
                                    adjustment_parameters._gain_digits,
                                    decibal);
    range_adjuster = new UTAdjuster(&display,
                                    &adjustment_parameters._range,
                                    adjustment_parameters._range_digits,
                                    meters);


    view_components[0] = main;
    active_component_idx = 0;
    active_component = main;
    
    redrawAll();
}

boolean UTView::isRunning() {
    return graph->isRunning();
}

void UTView::handlePress(input_t i) {
    view_t new_view = active_component->buttonPress(i);
    switch(new_view) {
        case NONE:
            return;
        case BACK:
            Serial.println("Moving back a view...");
            removeTopView();
            return;
        case MENU:
            Serial.println("Switching to Menu view...");
            addView(menu);
            return;
        case MAIN:
            Serial.println("Switching to Main view...");
            exitToMainView();
            return;
        case DELAY:
            Serial.println("Opening Delay Adjuster...");
            addView(delay_adjuster);
            return;
        case GAIN:
            Serial.println("Opening Gain Adjuster...");
            addView(gain_adjuster);
            return;
        case RANGE:
            Serial.println("Opening Range Adjuster...");
            addView(range_adjuster);
            return;
        case CALIBRATE:
            Serial.println("Opening Calibration tool...");
            return;
          
    }
}

void UTView::populateAdjustmentParams() {
    adjustment_parameters._delay = 0.0;
    adjustment_parameters._range = 1.0;
    adjustment_parameters._gain = 3.0;

    for(uint8_t i = 0; i < ADJUSTMENT_VALUE_DIGIT_COUNT; i++) {
        adjustment_parameters._delay_digits[i] = 0;
        adjustment_parameters._range_digits[i] = 0;
        adjustment_parameters._gain_digits[i] = 0;
    }

    adjustment_parameters._range_digits[1] = 1;
    adjustment_parameters._gain_digits[1] = 3;
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

void UTView::addView(UTComponent *new_view) {
    //check for out of bounds
    active_component_idx++;
    if(active_component_idx > MAX_COMPONENT_IDX) {
        Serial.println("ERROR - UI component stack size limit reached!");
        active_component_idx--;
        return;
    }

    view_components[active_component_idx] = new_view;
    active_component = new_view;
    active_component->create(true);
}

void UTView::removeTopView() {
    if(active_component_idx == 0) {
        Serial.println("ERROR - Trying to delete main view... aborting");
        return;
    }

    view_components[active_component_idx] = NULL;
    active_component_idx--;
    active_component = view_components[active_component_idx];
    redrawAll();
}

void UTView::exitToMainView() {
    //remove all pointers to anything above main
    for(uint8_t i = 1; i <= active_component_idx; i++) {
        view_components[i] = NULL;
    }

    active_component_idx = 0;
    active_component = main;
    redrawAll();
}

void UTView::redrawAll() {
    display.clearDisplay();
    display.setTextSize(1);
    for(uint8_t i = 0; i <= active_component_idx; i++) {
        if(i == 0)
            main->showGraph();
        view_components[i]->create(false);
    }
    display.display();
}






