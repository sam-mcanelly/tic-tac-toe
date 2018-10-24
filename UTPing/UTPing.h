#ifndef UTPing_h
#define UTPing_h

#include <ADC.h>
#include <ADC_Module.h>
#include <UTTypes.h>
#include "Arduino.h"

class UTPing
{
  public:
    UTPing(int _output_pin, int _input_pin, long _prop_offset) {
      pinMode(_output_pin, OUTPUT);
      pinMode(_input_pin, INPUT);
      output_pin = _output_pin;
      input_pin = _input_pin;
      propogation_offset = _prop_offset;

      adc = new ADC();

      pinMode(A10, INPUT);
      pinMode(A11, INPUT);

      adc->setConversionSpeed(ADC_CONVERSION_SPEED::HIGH_SPEED_16BITS, ADC_1);
      adc->setSamplingSpeed(ADC_SAMPLING_SPEED::HIGH_SPEED);
      adc->enableCompare(adc->getMaxValue(ADC_1), 0, ADC_1);
    }

    UTPing(int _output_pin, int _input_pin, long _prop_offset, double _mm) {
      mm = _mm;
      UTPing(_output_pin, _input_pin, _prop_offset);
    }

    ~UTPing() {
      delete adc;
    }

    int millimeters(long duration);

    void fire();
    void setStartDelay(double delay);
    void setPulseDelay(double delay);

    //this is the starting point for sending
    //and receiving signals
    //the frame buffer is of size
    //FRAME_POINT_COUNT
    void getNextFrame(XYPos_t *frame_buffer);

    void startReading();
    void stopReading();

    //function for testing
    void readSignal(XYPos_t *frame_buffer);


    
  private:
    int output_pin;
    int input_pin;
    long mm = 0;
    double start_delay = 0;
    double pulse_delay = 0.2;
    long propogation_offset = 0;

    ADC *adc;
};

#endif
