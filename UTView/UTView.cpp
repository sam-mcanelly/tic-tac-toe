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

    graph = new UTGraph(&display, &adjustment_parameters);
    main = new UTMain(&display, graph);
    menu = new UTMenu(&display);
    delay_adjuster = new UTAdjuster(&display,
                                    &adjustment_parameters._delay,
                                    adjustment_parameters._delay_digits,
                                    micro_seconds,
                                    DELAY_EEPROM_START);
    gain_adjuster = new UTAdjuster(&display,
                                    &adjustment_parameters._gain,
                                    adjustment_parameters._gain_digits,
                                    decibal,
                                    GAIN_EEPROM_START);
    range_adjuster = new UTAdjuster(&display,
                                    &adjustment_parameters._range,
                                    adjustment_parameters._range_digits,
                                    meters,
                                    RANGE_EEPROM_START);


    view_components[0] = main;
    active_component_idx = 0;
    active_component = main;
    
    redrawAll();
}

boolean UTView::isRunning() {
    return graph->isActive();
}

void UTView::handlePress(input_t i) {
    view_t new_view = active_component->buttonPress(i);
    switch(new_view) {
        case NONE:
            return;
        case BACK:
            removeTopView();
            return;
        case MENU:
            addView(menu);
            return;
        case MAIN:
            exitToMainView();
            return;
        case DELAY:
            addView(delay_adjuster);
            return;
        case GAIN:
            addView(gain_adjuster);
            return;
        case RANGE:
            addView(range_adjuster);
            return;
        case CALIBRATE:
            return;
          
    }
}

void UTView::populateAdjustmentParams() {
    adjustment_parameters._delay = (float)EEPROM.read(DELAY_EEPROM_START);
    adjustment_parameters._range = (float)EEPROM.read(RANGE_EEPROM_START);
    adjustment_parameters._gain = (float)EEPROM.read(GAIN_EEPROM_START);

    #if(DEBUGGING_MODE == true)
        Serial.print("Loaded delay from EEPROM: ");
        Serial.println(adjustment_parameters._delay);
        Serial.print("Loaded gain from EEPROM: ");
        Serial.println(adjustment_parameters._gain);
        Serial.print("Loaded range from EEPROM: ");
        Serial.println(adjustment_parameters._range);
    #endif
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
    delay(2000);
    display.stopscroll();
    display.clearDisplay();   // clears the screen and buffer
    display.display();
}

void UTView::addView(UTComponent *new_view) {
    //check for out of bounds
    active_component_idx++;
    if(active_component_idx > MAX_COMPONENT_IDX) {

        #if(DEBUGGING_MODE == true)
            Serial.println("ERROR - UI component stack size limit reached!");
        #endif

        active_component_idx--;
        return;
    }

    view_components[active_component_idx] = new_view;
    active_component = new_view;
    active_component->create(true);
}

void UTView::removeTopView() {
    if(active_component_idx == 0) {

        #if(DEBUGGING_MODE == true)
            Serial.println("ERROR - Trying to delete main view... aborting");
        #endif

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






