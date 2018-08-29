/****************************************
 * Ultrasonic Flaw Detector
 * Author(s): Sam McAnelly, 
 * Oklahoma State University
 * ECEN 4013
 * 
 * Note: The SSD1306 drivers must be 
 * configure to use a display type
 * that is 128x64. This can be set
 * in the Adafruit_SSD1306.h file.
 * Look for SSD1306_128_64 and the i2c
 * address definition
 * 
 * The address used for our display
 * is 0x3C
 * 
 ****************************************/
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

// This value can be found on 
// the display
#define OLED_ADDR   0x3D
#define OLED_RESET  4

Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
}

void loop() {
  

}
