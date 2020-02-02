#include <avr/interrupt.h>
#include <avr/io.h>
#include <Arduino.h>

long timer;
int distance;
int temperature;

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
  //Temperatur- und Abstandsmessung
  tempDistSetup();
  setEchoPins(0, 0); //Setze die pins für den Abstandsensor aus denen gelesenw erden soll das erster ist der Trigger-, das zweite der Echopin
  timer = millis(); 
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
  
  //Temperatur- und Abstandsmessung
  
  temperature = dallas(4, 0);
  
  if(millis() - timer >= 100){
	measureDistance();
	timer = millis();  
  }
  
  distance = calculateDistance();
  
}

void lcdMenu() {
  lcd.println("Platzhalter");

  
}
