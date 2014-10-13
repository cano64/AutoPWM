/*

*/


#include "AutoPWM.h"


AutoPWM::AutoPWM(uint8_t apin, uint16_t avoltLow, uint16_t avoltHigh, uint8_t apwmLow, uint8_t apwmHigh) : 
  pin(apin), voltLow(avoltLow), voltHigh(avoltHigh), pwmLow(apwmLow), pwmHigh(apwmHigh), pwm(0)
{
  digitalWrite(this->pin, LOW);
  pinMode(this->pin, OUTPUT);
}


void AutoPWM::autoPrescaler(uint8_t excludeTimer0) {
#if defined( __AVR_ATmega328P__ )  
  switch(digitalPinToTimer(this->pin)) {
		case TIMER0A:
		case TIMER0B:
      if (!excludeTimer0) {
        TCCR0B = TCCR0B & 0b11111000 | 0x01;//00 = off, 01 = pre1, 02 = pre8, 03 = pre64, 04 = pre256
      }
      break;

		case TIMER1A:
		case TIMER1B:
      TCCR1B = TCCR1B & 0b11111000 | 0x01;//00 = off, 01 = pre1, 02 = pre8, 03 = pre64, 04 = pre256
      break;

		case TIMER2A:
		case TIMER2B:
      TCCR2B = TCCR2B & 0b11111000 | 0x01;//00 = off, 01 = pre1, 02 = pre8, 03 = pre32, 04 = pre64
      break;
  }
#endif
}


void AutoPWM::update(uint16_t volt, uint8_t force) {
  uint8_t npwm;
  if (volt < this->voltLow) {
    npwm = this->pwmLow;
  } else if (volt > this->voltHigh) {
    npwm = this->pwmHigh;
  } else {
    npwm = map(volt, this->voltLow, this->voltHigh, this->pwmLow, this->pwmHigh);
  }
  if (npwm < this->pwm || force) {
	this->pwm = npwm;
	analogWrite(this->pin, this->pwm);
  }
}


void AutoPWM::off() {
  this->pwm = 0;
  digitalWrite(this->pin, LOW);
}


//