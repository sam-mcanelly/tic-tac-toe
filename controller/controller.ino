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
#include <UTView.h>

#define IO_COUNT 5
#define LEFT_PIN 2
#define ENTER_PIN 3
#define UP_PIN 4
#define RIGHT_PIN 5
#define DOWN_PIN 6

uint8_t buttonPins[IO_COUNT] = {UP_PIN, DOWN_PIN, LEFT_PIN, RIGHT_PIN, ENTER_PIN};

UTView view;

void setup() {
  //start serial for debugging purposes
  Serial.begin(9600);

  //initialize inputs
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(ENTER_PIN, INPUT_PULLUP);
  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  pinMode(DOWN_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENTER_PIN), handleInterrupt, LOW);
  
  view.begin();
  
}

void loop() {
  //check button input if the
  //transducer is not running
  if(!view.isRunning())
  {
    checkButtons();
  }

  

}

void handleInterrupt()
{
  view.handlePress(4); //enter's position in the array
}

void checkButtons()
{
  for(uint8_t i = 0; i < IO_COUNT; i++)
  {
    int input = digitalRead(buttonPins[i]);
    Serial.println(input);
    if(input == LOW)
    {
      delay(200); //debounce
      view.handlePress(i);
    }
    
  }
}

