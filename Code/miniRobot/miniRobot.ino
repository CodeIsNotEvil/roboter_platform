/*
 * modularer Mini Roboter mit diversen Sensoren
 * 
 * 
 */
//Funk
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE A0
#define CSN 3
RF24 radio(A0, 3); // CE, CSN

byte commands[32];       //byte 0 = command




void inline clearCommands() {
  for(uint8_t i=0; i<32; i++) {
    commands[i] = 0xFF;
  }
}

const byte address[6] = "00001";
const byte address2[6] = "00002";
//Kommandos
#define nothing 9 //reset/nichts tun
#define speedA 1 // set speed A + speed
#define dirA 2 // set direction A + dir
#define speedB 3 // set speed B + speed
#define dirB 4 // set direction B + dir
#define goDrive 5 //go + time to go
#define stopDrive 6 //stop
#define getTemp 7 //get temperature
#define timeToDrive 8 //Zeitdauer des fahrens
#define getDistance 10 //Abstand zu Objekten

//Motortreiber
#include <L298N.h>

#define BEEP 14     //Motoren drehen bei diesem PWM Wert nicht, aber fiepen
L298N drive;


volatile int pwmA = 0;
volatile int pwmB = 0;
bool forwardA = true;
bool forwardB = true;
volatile bool driveOn = false;

volatile uint32_t driveTimeout = 0;
volatile uint32_t driveTimeDiff = 0;

volatile bool startNewMeasurement = true;

volatile uint32_t pulseStart = 0;
volatile uint32_t pulseLength = 1;

volatile bool newResult = false;

uint32_t timer = 0;
int16_t temperature = 0;
uint16_t distance = 50;

void setup() {
  Serial.begin(115200);
//  motorA.setPWM16(2,RESOLUTION);
//  motorB.setPWM16(2,RESOLUTION);
  radio.begin();
  radio.openWritingPipe(address2);
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  clearCommands();
  
  //Temperatur- und Abstandsmessung
  
  setEchoPins(A2, 6); //16: A2, 6: D6
  tempDistSetup();
  timer = millis(); 
}

void loop() {
  //Temperatur- und Abstandsmessung 
  if((millis() - timer) >= 100){
    temperature = dallas(4, 0); 
    if(startNewMeasurement) {
      measureDistance();
    } 
    timer = millis();
  }
  if(newResult) {
       // Serial.println("berechnen");
        distance = calculateDistance();
      }
//wurden Kommandos empfangen?  
  if (radio.available()) {
    radio.read(&commands, sizeof(commands));
    commandInterpretation();
  }
//Antrieb abschalten wenn kein neuer Fahrbefehl kommt
  if(((millis() - driveTimeDiff) > driveTimeout)) {
    pwmA = 0;
    pwmB = 0;
  }

//Wenn Mindestdistanz unterschritten, stopp 
    if(distance < 20){
    if(pwmA < 0 && pwmB < 0){
        pwmA = 0;
        pwmB = 0;
      }
    }
    drive.setPWM_A(pwmA);
    drive.setPWM_B(pwmB); 
}

void commandInterpretation() {
  for(uint8_t i = 0; i < 28; i += 3) {
    switch(commands[i]) {
      case nothing :  {
                      pwmA = 0;
                      pwmB = 0;
                      forwardA = true;
                      forwardB = true;
                      driveOn = false;
                      break;
      }
      case speedA :   {
                      int temp1;
                      temp1 = (0xFF00 & (commands[i+1] << 8));
                      temp1 |= (0x00FF & commands[i+2]);
                      pwmA = temp1;
                      break;
      }
      case dirA :     {
                      bool temp2 = commands[i+2];
                      break;
      }
      case speedB :   {
                      int temp3;
                      temp3 = (0xFF00 & (commands[i+1] << 8));
                      temp3 |= (0x00FF & commands[i+2]);
                      pwmB = temp3; 
                      break;
      }
      case dirB :     {
                      bool temp4;
                      temp4 = commands[i+2];
                      break;
      }
      case goDrive :  {
                      driveOn = true;  
                      break;
      }
      case stopDrive : {
                      driveOn = false;      
                      break;
      }
      case getTemp :  { 
                      //Serial.println("Senden!");                    
                      radio.stopListening();     
                      int16_t sendData = temperature;               
                      radio.write(&sendData, sizeof(int16_t));
                      radio.startListening();
                      break;
      }
      case timeToDrive : {
                        uint16_t driveTime = 0;
                        driveTime = (0xFF00 & (commands[i+1] << 8));
                        driveTime |= (0x00FF & commands[i+2]); 
                        driveTimeout = (uint32_t)driveTime;
                        driveTimeDiff = millis();
                        //Serial.println(driveTimeout);
                        break;
      }
      default :  {  
                        break; 
      }
    }
  }
  clearCommands();
  
}
