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

}

void loop() {
  //lcdMenu();
  
  while(!tasten.getButtonCycle(buttonStart)) {
    manualDigitalDrive();
  } 
  tasten.clearButton(buttonStart);
 while(!tasten.getButtonCycle(buttonStart)){
    motorMapping();
  }
  tasten.clearButton(buttonStart);
  while(!tasten.getButtonCycle(buttonStart)){
    joystickSteuerung(); //TODO ()

    
  }
  tasten.clearButton(buttonStart);
  
<<<<<<< HEAD
  //Temperatur- und Abstandsmessung
  /*
  temperature = dallas(4, 0);
  
  if(millis() - timer >= 100){
	measureDistance();
	timer = millis();  
  }
  
  distance = calculateDistance();
  */
=======
>>>>>>> 48327ec5c42c4d70afa8e9c00bbf52ab2db2ca05
}

void lcdMenu() {
  lcd.println("Platzhalter");

  
}
