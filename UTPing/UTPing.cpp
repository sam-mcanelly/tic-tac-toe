#include "WProgram.h"
#include "UTPing.h"

UTPing::Ping(int outputPin, int inputPin)
{
  pinMode(outputPin, OUTPUT);
  pinMode(inputPin, INPUT)
  _outputPin = outputPin;
  _inputPin = inputPin;
  _in = 0;
  _cm = 0;
  _duration = -1;
}

UTPing::Ping(int outputPin, int inputPin, double in, double cm)
{
  pinMode(pin, OUTPUT);
  _outputPin = outputPin;
  _inputPin = inputPin;
  _in = in;
  _cm = cm;
  _duration = -1;
  _startDelay = 1;
  _pulseDelay = 0.2;
}

void UTPing::fire()
{
  digitalWrite(_outputPin, LOW);
  delayMicroseconds(_startDelay);
  digitalWrite(_outputPin, HIGH);
  delayMicroseconds(_pulseDelay);
  digitalWrite(_outputPin, LOW);
  _duration = pulseIn(_inputPin, HIGH);
  
}

int UTPing::microseconds()
{
  return _duration;
}

double UTPing::inches()
{
  if(_duration != -1){
    return _duration / (74+_in) / 2;
  }else{
    return -1;
  }
}

double UTPing::centimeters()
{
  if(_duration != -1){
    return _duration / (29+_cm) / 2;
  }else{
    return -1;
  }
}

void UTPing::setPulseDelay(double delay)
{
  _pulseDelay = delay;
}

void UTPing::setStartDelay(double delay)
{
  _startDelay = delay;
}