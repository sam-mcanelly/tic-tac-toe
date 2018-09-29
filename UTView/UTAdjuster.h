/****************************************
 * 
 * Ultrasonic Flaw Detector - UTAdjuster
 * Author(s): Sam McAnelly, 
 * Oklahoma State University
 * ECEN 4013
 * 
 ****************************************/

#ifndef UTAdjuster_h
#define UTAdjuster_h

#include "UTComponent.h"

class UTAdjuster : public UTComponent {
    public:
        UTAdjuster(Adafruit_SSD1306 *_display, 
                   float *val, 
                   uint8_t digits[ADJUSTMENT_VALUE_DIGIT_COUNT], 
                   String _units,
                   int _EEPROM_save_start){

            display = _display;
            adjustment_value = val;
            adjustment_value_digits = digits;
            EEPROM_save_start = _EEPROM_save_start;
            units = _units;
            adjusting = false;
            digit_cursor_position = 0;
        }

        void create(boolean show);
        XYPos_t getCursorPositionLocation();
        XYPos_t getPositionXY(uint8_t position);

        void changeCursorPosition(uint8_t new_position);
    private:
        String units;
        float *adjustment_value;
        uint8_t *adjustment_value_digits;
        uint8_t digit_cursor_position;
        boolean adjusting;

        int EEPROM_save_start;

        //adjuster screen input positions
        XYPos_t save_position = {42, 32};
        XYPos_t exit_position = {74, 32};

        XYPos_t d1_position = {34, 14};
        XYPos_t d2_position = {49, 14};
        XYPos_t d3_position = {69, 14};
        XYPos_t d4_position = {84, 14};

        XYPos_t decimal_position = {58, 14};
        XYPos_t unit_position = {98, 20};

        XYPos_t adjusterInputPositions[ADJUSTMENT_IO_COUNT] = {save_position, exit_position};
        XYPos_t adjusterDigitPositions[ADJUSTMENT_VALUE_DIGIT_COUNT] = {d1_position, d2_position, d3_position, d4_position};
        String adjusterDigitStrings[ADJUSTMENT_VALUE_DIGIT_COUNT] = {"0", "0", "0", "0"};
        String adjusterViewStrings[ADJUSTMENT_STRING_COUNT] = {"save", "exit"};

        void setCursor(XYPos_t position);

        view_t leftPress();
        view_t rightPress();
        view_t upPress();
        view_t downPress();
        view_t enterPress(); 

        void drawAdjusterContainer();
        void drawAdjusterButtons();
        void drawAdjusterDigits();
        void drawAdjusterUnits();

        void updateAdjusterDigitStrings();

        void incrementAdjusterDigit(uint8_t digit);
        void decrementAdjusterDigit(uint8_t digit);

        void updateAdjusterDigit(uint8_t digit);

        void saveAdjustmentValue();
        void discardAdjustmentValue();
};

#endif