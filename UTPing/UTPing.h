#ifndef UTPing_h
#define UTPing_h

#include "Arduino.h"

class UTPing
{
  public:
    UTPing(int outputPin, int inputPin);
    UTPing(int outputPin, int inputPin, double in, double cm);

    int microseconds();

    double inches();
    double centimeters();

    void fire();
    void setStartDelay(double delay);
    void setPulseDelay(double delay);

    
  private:
    int _outputPin;
    int _inputPin;
    double _in;
    double _cm;
    long _duration;
    double _startDelay;
    double _pulseDelay;
};

#endif
