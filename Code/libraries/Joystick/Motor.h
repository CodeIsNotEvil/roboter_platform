#ifndef __MOTOR__
#define __MOTOR__

#include <Arduino.h>

class Motor {
  public:
    int16_t highestValue;
    int16_t lowestValue;
    int16_t PWMValue;

  public:
    Motor(int16_t lowestValue, int16_t highestValue);
};
#endif
