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

void UTPing::getNextFrame(XYPos_t *frame_buffer) {
  //send signal
  //wait for returning signal
  //receive returning signal
  //do distance and magnitude calculations
  //fill frame_buffer
  //exit
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

void UTPing::startReading() {
  adc->startContinuousDifferential(A10, A11, ADC_1);
}

void UTPing::stopReading() {
  adc->stopContinuous(ADC_1);
}

//test function for reading signals
void UTPing::readSignal(XYPos_t *frame_buffer) {
  for(int i = 0; i < 100; i++) {
    frame_buffer[i].y = adc->analogReadContinuous(ADC_1) / 10;
    //if(frame_buffer[i].y < 20) frame_buffer[i].y = 0;
    //else if(frame_buffer[i].y > 32768) frame_buffer[i].y = 30;
    frame_buffer[i].x = i * 4;
    //delay(1);
  }

  for(int i = 0; i < 100; i++) {
    Serial.print(frame_buffer[i].y);
    Serial.print(", ");
  }
  Serial.println();
  adc->printError();
}
