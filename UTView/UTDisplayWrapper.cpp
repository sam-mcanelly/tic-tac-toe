/****************************************
 * 
 * Ultrasonic Flaw Detector - UTDisplayWrapper
 * Author(s): Sam McAnelly, 
 * Oklahoma State University
 * ECEN 4013
 * 
 * Wraps the Adafruit_* libraries for generic
 * manipulation of displays
 * 
 ****************************************/

#include "UTDisplayWrapper.h"

/**
 * 
 * 
 *      Public functions
 * 
 * 
 * */

/**
 * Functions redefined from Adafruit_GFX
 * */

template <class T>
void UTDisplayWrapper<T>::begin() {
    #if(DISPLAY_TYPE == SSD_1306)
        adafruit_display->begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    #elif(DISPLAY_TYPE == ST_7735)
        adafruit_display->initR(INITR_BLACKTAB);
        adafruit_display->setRotation(1);
    #endif 
}

template<class T>
void UTDisplayWrapper<T>::display() {
    #if(DISPLAY_TYPE == SSD_1306)
        adafruit_display->display();
    #endif
}

template<class T>
void UTDisplayWrapper<T>::clearDisplay() {
    #if(DISPLAY_TYPE == SSD_1306)
        adafruit_display->clearDisplay();
    #elif(DISPLAY_TYPE == ST_7735)
        adafruit_display->fillScreen(ST7735_BLACK);
    #endif
}

template<class T>
void UTDisplayWrapper<T>::setTextSize(uint8_t size) {
    adafruit_display->setTextSize(size);
}

template<class T>
void UTDisplayWrapper<T>::setTextColor(uint16_t color) {
    #if(DISPLAY_TYPE == SSD_1306)
        if(color < _CYAN) color = BLACK;
        else color = WHITE;
    #endif

    adafruit_display->setTextColor(color);
}

template<class T>
void UTDisplayWrapper<T>::setTextColor(uint16_t color, uint16_t backgroundcolor) {
    #if(DISPLAY_TYPE == SSD_1306)
        if(color < _CYAN) {
            color = _BLACK;
            backgroundcolor = WHITE;
        }
        else {
            color = WHITE;
            backgroundcolor = BLACK;
        }
    #endif

    adafruit_display->setTextColor(color, backgroundcolor);
}

template<class T>
void UTDisplayWrapper<T>::setTextWrap(boolean w) {
    adafruit_display->setTextWrap(w);
}

template<class T>
void UTDisplayWrapper<T>::setCursor(uint16_t x, uint16_t y) {
    adafruit_display->setCursor(x, y);
}

template<class T>
void UTDisplayWrapper<T>::print(String s) {
    adafruit_display->print(s);
}

template<class T>
void UTDisplayWrapper<T>::println(String s) {
    adafruit_display->println(s);
}

template<class T>
void UTDisplayWrapper<T>::startscrollright(uint8_t start, uint8_t stop) {
    #if(DISPLAY_TYPE == SSD_1306)
        adafruit_display->startscrollright(start, stop);
    #else
        Serial.println("Scrolling not supported!");
    #endif
}

template<class T>
void UTDisplayWrapper<T>::startscrollleft(uint8_t start, uint8_t stop) {
    #if(DISPLAY_TYPE == SSD_1306)
        adafruit_display->startscrollleft(start, stop);
    #else
        Serial.println("Scrolling not supported!");
    #endif
}

template<class T>
void UTDisplayWrapper<T>::stopscroll(void) {
    #if(DISPLAY_TYPE == SSD_1306)
        adafruit_display->stopscroll();
    #else
        Serial.println("Scrolling not supported!");
    #endif
}

template<class T>
void UTDisplayWrapper<T>::drawFastVLine(uint16_t x0, uint16_t y0, uint16_t length, uint16_t color) {
    #if(DISPLAY_TYPE == SSD_1306)
        if(color < _CYAN) color = BLACK;
        else color = WHITE;
    #endif

    adafruit_display->drawFastVLine(x0, y0, length, color);
}

template<class T>
void UTDisplayWrapper<T>::drawFastHLine(uint16_t x0, uint16_t y0, uint16_t length, uint16_t color) {
    #if(DISPLAY_TYPE == SSD_1306)
        if(color < _CYAN) color = BLACK;
        else color = WHITE;
    #endif
    
    adafruit_display->drawFastHLine(x0, y0, length, color);
};

template<class T>
void UTDisplayWrapper<T>::drawRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color) {
    #if(DISPLAY_TYPE == SSD_1306)
        if(color < _CYAN) color = BLACK;
        else color = WHITE;
    #endif
    
    adafruit_display->drawRect(x0, y0, w, h, color);
}

template<class T>
void UTDisplayWrapper<T>::fillRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color) {
    #if(DISPLAY_TYPE == SSD_1306)
        if(color < _CYAN) color = BLACK;
        else color = WHITE;
    #endif
    
    adafruit_display->fillRect(x0, y0, w, h, color);
}

template<class T>
void UTDisplayWrapper<T>::drawRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint16_t color) {
    #if(DISPLAY_TYPE == SSD_1306)
        if(color < _CYAN) color = BLACK;
        else color = WHITE;
    #endif
    
    adafruit_display->drawRoundRect(x0, y0, w, h, radius, color);
}

template<class T>
void UTDisplayWrapper<T>::fillRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint16_t color) {
    #if(DISPLAY_TYPE == SSD_1306)
        if(color < _CYAN) color = _BLACK;
        else color = _WHITE;
    #endif
    
    adafruit_display->fillRoundRect(x0, y0, w, h, radius, color);
}

template<class T>
void UTDisplayWrapper<T>::drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    #if(DISPLAY_TYPE == SSD_1306)
        if(color < _CYAN) color = BLACK;
        else color = WHITE;
    #endif
    
    adafruit_display->drawTriangle(x0, y0, x1, y1, x2, y2, color);
}

template<class T>
void UTDisplayWrapper<T>::fillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    #if(DISPLAY_TYPE == SSD_1306)
        if(color < _CYAN) color = BLACK;
        else color = WHITE;
    #endif
    
    adafruit_display->fillTriangle(x0, y0, x1, y1, x2, y2, color);
}

/**
 * End functions redefined from Adafruit_GFX
 * 
 * The following only work for ST7735
 * */

#if(DISPLAY_TYPE == ST_7735)
    template<class T>
    void UTDisplayWrapper<T>::drawButton(uint16_t x0, uint16_t y0, String text, button_size_t size) {
        button_params_t button_params;

        switch(size){
            case SMALL:
                button_params = small_button;
                break;
            case MEDIUM:
                button_params = medium_button;
                break;
            case LARGE:
                button_params = large_button;
                break;
        }

        //clear
        fillRect(x0, y0, button_params.w, button_params.h, _BLACK);
        //outline
        drawRect(x0, y0, button_params.w, button_params.h, _WHITE);
        //populate text
        setCursor(x0 + 2, y0 + 2);
        setTextColor(_WHITE);
        println(text);
    }

    template<class T>
    void UTDisplayWrapper<T>::selectButton(uint16_t x0, uint16_t y0, String text, button_size_t size) {
        button_params_t button_params;
        
        switch(size){
            case SMALL:
                button_params = small_button;
                setTextSize(1);
                break;
            case MEDIUM:
                button_params = medium_button;
                setTextSize(1);
                break;
            case LARGE:
                button_params = large_button;
                setTextSize(2);
                break;
        }

        drawRect(x0, y0, button_params.w, button_params.h, _GREEN);
        setCursor(x0 + 2, y0 + 2);
        setTextColor(_GREEN);
        println(text);
        setTextColor(_WHITE);
    }

    template<class T>
    void UTDisplayWrapper<T>::deselectButton(uint16_t x0, uint16_t y0, String text, button_size_t size) {
        button_params_t button_params;
        
        switch(size){
            case SMALL:
                button_params = small_button;
                setTextSize(1);
                break;
            case MEDIUM:
                button_params = medium_button;
                setTextSize(1);
                break;
            case LARGE:
                button_params = large_button;
                setTextSize(2);
                break;
        }

        drawRect(x0, y0, button_params.w, button_params.h, _WHITE);
        setCursor(x0 + 2, y0 + 2);
        setTextColor(_WHITE);
        println(text);
    }
#endif

/**
 * 
 * 
 *      End public functions
 * 
 * 
 * */

/**
 *  Template definitions for each supported display 
 * 
 * */

#if(DISPLAY_TYPE == SSD_1306)
    template class UTDisplayWrapper<Adafruit_SSD1306>;
#elif(DISPLAY_TYPE == ST_7735)
    template class UTDisplayWrapper<Adafruit_ST7735>;
#endif
