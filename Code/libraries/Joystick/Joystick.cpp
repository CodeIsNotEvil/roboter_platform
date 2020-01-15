#include "Joystick.h"

Joystick::Joystick(uint16_t x_pin, uint16_t y_pin, int16_t lowestValue, int16_t highestValue, uint16_t spaceing) {
  this -> x_pin = x_pin;
  this -> y_pin = y_pin;
  this -> lowestValue = lowestValue;
  this -> highestValue = highestValue;
  this -> spaceing = spaceing;
}

void Joystick::checkJoystickInput() {
  this -> xAxisReading = analogRead(x_pin);
  this -> yAxisReading = analogRead(y_pin);
  //9-bit reichen, der ADC schafft bestenfalls 8-bit praezision
  (this -> xAxisReading) = (this -> xAxisReading) >> 1;
  (this -> yAxisReading) = (this -> yAxisReading) >> 1;
}
