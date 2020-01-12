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
  driveTimeout = 50;
/*
  commands[0] = speedA;
  commands[1] = 0xFF & (pwmA >> 8);
  commands[2] = 0xFF & pwmA;
  
  commands[3] = speedB;
  commands[4] = 0xFF & (pwmB >> 8);
  commands[5] = 0xFF & pwmB;

  commands[6] = goDrive;

  commands[9] = timeToDrive;
  commands[10] = 0xFF & (driveTimeout >> 8);
  commands[11] = 0xFF & driveTimeout; */
  clearCommands();
}

void loop() {
//char text[32] = "Hello";
 // radio.write(&commands, sizeof(commands));
  //lcdMenu();
  //delay(10000);
  manualDrive();
}

void lcdMenu() {
  lcd.println("Platzhalter");
  
  if(tasten.getButtonCycle(buttonUp)) {

    tasten.clearAllButtons();
  }
  if(tasten.getButtonCycle(buttonDown)) {

    tasten.clearAllButtons();
  }
  
}

void manualDrive() {
  bool goOn = false;
  while(!tasten.getButtonCycle(buttonStart)) {
    clearCommands();
    if(!tasten.getAnyPressed()) {
      lcd.clear();
      lcd.println("Warte...");
    }
    if(tasten.checkButton(buttonB) || tasten.checkButton(buttonUp)) {
            pwmA = -215;
            pwmB = -255;
           // tasten.clearButton(buttonB);
            lcd.clear();
            lcd.println("geradeaus fahren");
            goOn =true;
    }
    if(tasten.checkButton(buttonC) || tasten.checkButton(buttonDown)) {
            pwmA = 100;
            pwmB = 255;
           // tasten.clearButton(buttonC);
            lcd.clear();
            lcd.println("rueckwaerts fahren");
            goOn =true;
     }
    if(tasten.checkButton(buttonRight)) {
        pwmA = -100;  //rechter Motor
        pwmB = 100;
        //tasten.clearButton(buttonRight);
        lcd.clear();
        lcd.println("rechts lenken");
            goOn =true;
    } 
    if(tasten.checkButton(buttonLeft)) {
        pwmB = -100;
        pwmA = 100;
        //tasten.clearButton(buttonLeft);
        lcd.clear();
        lcd.println("links lenken");
            goOn =true;
    }
      if(goOn) {
        commands[0] = speedA;
        commands[1] = highByte(pwmA);
        commands[2] = lowByte(pwmA);
        commands[3] = speedB;
        commands[4] = highByte(pwmB);
        commands[5] = lowByte(pwmB);
        commands[6] = timeToDrive;
        commands[7] = highByte(driveTimeout);
        commands[8] = lowByte(driveTimeout);
        commands[9] = goDrive;
        radio.write(&commands, sizeof(commands));
        goOn = false;
      }
    }
    tasten.clearAllButtons();
}

ISR(TIMER2_COMPA_vect) { // called by timer2
  tasten.checkButtons();  //Aufruf 1-mal pro Millisekunde
}
