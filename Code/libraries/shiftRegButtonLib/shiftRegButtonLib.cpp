#include "shiftRegButtonLib.h"

 shiftRegButton::shiftRegButton() {

  //init Pins
  shiftDatPORT &= ~shiftDatPin;
  shiftClkPORT &= ~shiftClkPin;

  //shiftInDDR &= ~shiftInPin;
  shiftDatDDR |= shiftDatPin;
  shiftClkDDR |= shiftClkPin;

  shiftInPORT |= shiftInPin;

  //init all flags
  shiftDatHi;
  for(uint8_t i = 0; i < numberOfButtons; i++, shiftClk()) {
 //  buttonsPressed[i] = false;   
 //  buttonsCycle[i] = false;  
 
   buttonsTime[i] = 0;
//   cycleFlag[i] = false;
   //init shiftreg outputs to all 1's
  }
   buttonsPressed = 0;   
   buttonsCycle = 0;
   cycleFlag = 0;
 }

 shiftRegButton::checkButtons(void) {
  //this procedure is needed by the 74HC595, other shift registers' behaviour may differ. See the datasheet of your part for more informations.
  shiftDatLo;	//
  shiftClk();	//zero to shift stage 0
  shiftDatHi;	//
  shiftClk();	//zero to parallel output 0
  for(uint8_t i = 0; i < numberOfButtons; i++, shiftClk()) {
    //is button i actually pressed?
    if(buttonsInput()) {
      buttonsPressed |= 1 << i;
     // buttonsPressed[i] = true;
     // cycleFlag[i] = true;
      cycleFlag |= 1 << i;
      buttonsTime[i]++;
    } else {
     //  buttonsPressed[i] = false;
       buttonsPressed &= ~(1 << i);
       buttonsTime[i] = 0;
    }
    checkButtonCycle(i);
    //increase the time button i is pressed, or clear if it is not pressed anymore
  }
 }

 bool shiftRegButton::checkButton(uint8_t n) {
//  return buttonsPressed[n];
  return buttonsPressed & (1 << n);
 }
 
 shiftRegButton::checkButtonCycle(uint8_t n) {
//  if(!buttonsPressed[n] && cycleFlag[n]) {
  if(!(buttonsPressed & (1 << n)) && (cycleFlag & (1 << n)) ) {
//   buttonsCycle[n] = true;
   buttonsCycle |= 1 << n;
//   cycleFlag[n] = false;
   cycleFlag &= ~(1 << n);
  }
 }
 
 shiftRegButton::clearButton(uint8_t buttonToBeCleared) {
//   buttonsCycle[buttonToBeCleared] = false;
   buttonsCycle &= ~(1 << buttonToBeCleared);
 }
 
 shiftRegButton::clearAllButtons() {
  for(uint8_t i = 0; i < numberOfButtons; i++) {  
//   buttonsCycle[i] = false;
   buttonsCycle &= ~(1 << i);
  }
 }

 bool shiftRegButton::getButtonCycle(uint8_t n) {
//   return buttonsCycle[n];
   return buttonsCycle & (1 << n);
 }
 uint16_t shiftRegButton::getAnyPressed() {
   return buttonsPressed;
 }
