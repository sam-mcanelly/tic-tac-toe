tic-tac-toe
===========

To-Do List
----------

### UTView
- Add UTTray for rendering the bottom buttons/parameters
- Optimize graph states and state transitions
- Add Point,Line, and Magnitude to Graph
- Add Graph pause and inspection of last n frames
- Add UTPing object and determine where it will live
  and be passed around

### UTPing
- Add API for generating a signal manually
- Add API for generating a singal through the line driver
- Add ADC conversion for transducer input

- Experiments:
  - Read signal and output on display like an oscilloscope
  - Generate ranges of signals
  - (Maybe) get a piezo transducer from lab and test with
    ultrasonic distance calculation in the air


Usage
-----
- Compatibility : Currently only tested on Teensy 3.1/3.2
- First, ensure the teensyduino helper is installed : https://www.pjrc.com/teensy/td_download.html
- To use the provided libraries, copy UTView and UTPing into the following directory
  - /Applications/Arduino.app/Contents/Java/hardware/teensy/avr/libraries -> Mac
  - C:\Program Files (x86)\Arduino\hardware\teensy\avr\libraries -> Windows
- Button and potentiometer outputs/inputs are defined in UTTypes.h as well as the OLED address

- Definitions from UTTypes.h

  - OLED display (currently 0.96" SSD1306)
    - OLED_RESET  4
    - OLED_ADDR   0x3C
  
  - Buttons
    - LEFT_PIN 2
    - ENTER_PIN 3
    - UP_PIN 4
    - DOWN_PIN 5
    - RIGHT_PIN 6

  - Potentiometers
    - GAIN_PIN A3
    - RANGE_PIN A2
    - OFFSET_PIN A1
    - INSPECT_PIN A0
  
  
- Note: Don't make the git repository in the 'libraries' folder. Store the git repository somewhere
  easy to remember, then do all of the development work by editing the files directly in the 'libraries'
  folder. Once the results are satisfactory, copy the changes back into the folder containing the git
  repository.
