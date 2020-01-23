#include <avr/interrupt.h>
#include <avr/io.h>
#include <Arduino.h>

void inline clearCommands() {
  for(uint8_t i=0; i<32; i++) {
    commands[i] = 0xFF;
  }
}

void setup() {
  remoteControlInit(); 
  funkInit();
  Serial.begin(115200);
  driveTimeout = 10;

  clearCommands();
}

void loop() {
  //lcdMenu();
  while(!tasten.getButtonCycle(buttonStart)) {
    manualDigitalDrive();
  } 
  tasten.clearButton(buttonStart);
  while(!tasten.getButtonCycle(buttonStart)) motorMapping();
  tasten.clearButton(buttonStart);
  
}

void lcdMenu() {
  lcd.println("Platzhalter");

  
}
