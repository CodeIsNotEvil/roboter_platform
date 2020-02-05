#pragma once

#ifndef L298N_h
#define L298N_h

#include <Arduino.h>

#define PIN_A 0x01
#define PORT_A PORTB
#define DDR_A DDRB
#define PIN_B 128
#define PORT_B PORTD
#define DDR_B DDRD

#define PWMA OCR1B
#define PWMB OCR1A

class L298N {
 public:
  L298N();
  setPWM_A(int16_t pwmA);
  setPWM_B(int16_t pwmB);

 //private:

};

#endif
