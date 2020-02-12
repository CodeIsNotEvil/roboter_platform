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
  joystickInit(); //TODO
  clearCommands();
  renderTime = millis();
}

void loop() {
  //lcdMenu();
  
  while(!tasten.getButtonCycle(buttonStart)) {
    manualDigitalDrive();
    updateTemp();
      String temp_str = "T: " + String(temperature) + " Grad C";
      lcdLines[5] = temp_str;
    refreshLCD();
  } 
  tasten.clearButton(buttonStart); /*
 while(!tasten.getButtonCycle(buttonStart)){
    motorMapping();
    //updateTemp();
    refreshLCD();
  }
  tasten.clearButton(buttonStart); */
  while(!tasten.getButtonCycle(buttonStart)){
    joystickSteuerung(); //TODO ()
    //updateTemp();
    refreshLCD();
  }
  tasten.clearButton(buttonStart);
}

void lcdMenu() {
  lcd.println("Platzhalter");

  
}

void refreshLCD() {
  
  if((millis() - renderTime) >= renderTimeout) {
    lcd.clear();
    for(uint8_t i = 0; i < sizeof(lcdLines); i++) {
      lcd.gotoXY(0, i);
      lcd.print(lcdLines[i]);  
    }
    lcd.renderAll();
    renderTime = millis();
  }
}
