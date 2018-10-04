#include "UTPing.h"

void UTPing::fire() {
  digitalWrite(output_pin, LOW);
  delayMicroseconds(start_delay);
  digitalWrite(output_pin, HIGH);
  delayMicroseconds(pulse_delay);
  digitalWrite(output_pin, LOW);
  long duration = pulseIn(input_pin, HIGH);
  
}

void UTPing::setStartDelay(double delay) {
  start_delay = delay;
}

void UTPing::setPulseDelay(double delay) {
  pulse_delay = delay;
}

//THIS NEEDS TO BE CHANGED 
//IT WON'T WORK IN ITS CURRENT
//STATE
int UTPing::millimeters(long duration) {
  if(duration != -1){
    return (int)((duration / (29+mm) / 2) * 10);
  }else{
    return -1;
  }
}

//test function for reading signals
void UTPing::readSignal() {
  int value[100];  

  for(int i = 0; i < 100; i++) {
    value[i] = adc->analogRead(A9, ADC_0);
  }

  for(int i = 0; i < 100; i++) {
    Serial.print(value[i]);
    Serial.print(", ");
  }
  Serial.println();
  adc->printError();
}
