#include "Motor.h"

Motor::Motor(int16_t lowestValue, int16_t highestValue) {
  this -> highestValue = highestValue;
  this -> lowestValue = lowestValue;
  this -> PWMValue = 0;
}
