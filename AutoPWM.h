/*

*/

#ifndef AutoPWM_H
#define AutoPWM_H


#include "Arduino.h"


class AutoPWM {
  
  public:
    
    uint8_t pin;
    uint16_t voltLow;
    uint16_t voltHigh;
    uint8_t pwmLow;
    uint8_t pwmHigh;
    uint8_t pwm;
  
    AutoPWM(uint8_t apin, uint16_t avoltLow, uint16_t avoltHigh, uint8_t apwmLow, uint8_t apwmHigh);
    AutoPWM(uint8_t apin);
    void autoPrescaler(uint8_t excludeTimer0 = 1);
    void update(uint16_t volt, uint8_t force = 0);
    void setPWM(uint8_t apwm);
    void off();
  private:

}; //end of class AutoPWM



#endif
