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
#ifndef UTDisplayWrapper_H
#define UTDisplayWrapper_H

#include <Adafruit_GFX.h>
#include "UTTypes.h"

#if(DISPLAY_TYPE == SSD_1306)
    #include <Adafruit_SSD1306.h>
#elif((DISPLAY_TYPE == ST_7735))
    #include <Adafruit_ST7735.h>
#endif

template<class T>
class UTDisplayWrapper {
    public:
        UTDisplayWrapper<T>(T *_display) {
            adafruit_display = _display;
        }

        /**
         * Functions redefined from Adafruit_GFX
         * */

        void begin();

        void display();
        void clearDisplay();

        void setTextSize(uint8_t size);
        void setTextColor(uint16_t color);
        void setTextColor(uint16_t color, uint16_t backgroundcolor);
        void setTextWrap(boolean w);

        void setCursor(uint16_t x, uint16_t y);

        void print(String s);
        void println(String s);

        void startscrollright(uint8_t start, uint8_t stop);
        void startscrollleft(uint8_t start, uint8_t stop);
        void stopscroll(void);

        void drawFastVLine(uint16_t x0, uint16_t y0, uint16_t length, uint16_t color);
        void drawFastHLine(uint16_t x0, uint16_t y0, uint16_t length, uint16_t color);

        void drawRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color);
        void fillRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color);

        void drawRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint16_t color);
        void fillRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint16_t color);

        void drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
        void fillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

        /**
         * End of functions redefined from Adafruit_GFX
         * */

        void drawButton(uint16_t x0, uint16_t y0, String text, button_size_t size);

        void selectButton(uint16_t x0, uint16_t y0, String text, button_size_t size);
        void deselectButton(uint16_t x0, uint16_t y0, String text, button_size_t size);


    private:
        T * adafruit_display;
};

#endif