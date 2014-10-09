/*

*/


#include "AutoPWM.h"


AutoPWM::AutoPWM(uint8_t apin, uint16_t avoltLow, uint16_t avoltHigh, uint8_t apwmLow, uint8_t apwmHigh) : 
  pin(apin), voltLow(avoltLow), voltHigh(avoltHigh), pwmLow(apwmLow), pwmHigh(apwmHigh), pwm(0)
{
  digitalWrite(this->pin, LOW);
  pinMode(this->pin, OUTPUT);
}


void AutoPWM::autoPrescaler(uint8_t preserveMillis) {

}


void AutoPWM::update(uint16_t volt) {
  if (volt < this->voltLow) {
    this->pwm = this->pwmLow;
  } else if (volt > this->voltHigh) {
    this->pwm = this->pwmHigh;
  } else {
    this->pwm = map(volt, this->voltLow, this->voltHigh, this->pwmLow, this->pwmHigh);
  }
  analogWrite(this->pin, this->pwm);
}


void AutoPWM::off() {
  this->pwm = 0;
  digitalWrite(this->pin, LOW);
}


//