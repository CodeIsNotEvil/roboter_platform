#pragma once

#ifndef shiftRegButtonLib_h
#define shiftRegButtonLib_h

#include <Arduino.h>

#define numberOfButtons 11
//definitions for buttons
#define buttonUp 0
#define buttonLeft 2
#define buttonRight 1
#define buttonDown 3

#define buttonL1 4
#define buttonStart 5
#define buttonSelect 6
#define buttonR1 7

#define buttonA 9
#define buttonB 10
#define buttonC 8
//Pin and PORT assignments for shiftRegister(s)
#define shiftDatPin  0x01	//D8
#define shiftClkPin  0x40	//D6
#define shiftInPin   0x02	//D9

#define shiftDatPORT PORTB
#define shiftDatDDR  DDRB	// Should be DDRx, x = port name (B, C, D, etc.)

#define shiftClkPORT PORTD
#define shiftClkDDR  DDRD

#define shiftInPIN   PINB
#define shiftInPORT  PORTB
#define shiftInDDR   DDRB
//Macros
#define shiftDatLo (shiftDatPORT &= ~shiftDatPin)
#define shiftDatHi (shiftDatPORT |= shiftDatPin)
//74HC595 needs rising edge for sampling data
inline void shiftClk(void) 
{
 shiftClkPORT |= shiftClkPin;
 shiftClkPORT &= ~shiftClkPin;
}

inline bool buttonsInput(void)
{
 if((shiftInPIN &= shiftInPin) == 0) {
  return true;
 } else {
    return false;
 }
}

class shiftRegButton {
 public: 

  shiftRegButton();
  checkButtons(void);
//returns the state of a certain button
  bool checkButton(uint8_t n);
  checkButtonCycle(uint8_t n);
//clears the cycle flag of a certain button
  clearButton(uint8_t buttonToBeCleared);
//clears all cycle flags
  clearAllButtons();
//return, if a certain button has been pressed (complete cycle, Hi-Lo-Hi)
  bool getButtonCycle(uint8_t n);
//was any button pressed?
  uint16_t getAnyPressed();


 private:
   
//  volatile bool buttonsPressed[numberOfButtons];    //flags to represent the actual (debounced) state of a button, no clearing needed 
  volatile uint16_t buttonsPressed;		      //flags to represent the actual (debounced) state of a button, no clearing needed

//  volatile bool buttonsCycle[numberOfButtons];      //flags to represent if a button did a whole hi-lo-hi cycle,      clearing needed
  volatile uint16_t buttonsCycle;      //flags to represent if a button did a whole hi-lo-hi cycle,      clearing needed
  uint8_t buttonsTime[numberOfButtons];    //the time in milliseconds a button was actually pressed,      no clearing needed, no overflow detection (max = 255ms)
//  volatile bool cycleFlag[numberOfButtons];
  volatile uint16_t cycleFlag;
};

#endif
