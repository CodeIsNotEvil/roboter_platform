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
long timer;
int16_t temperature;
int distance = 0;

void inline clearCommands() {
  for(uint8_t i=0; i<32; i++) {
    commands[i] = 0xFF;
  }
}

const byte address[6] = "00001";
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
//#include <MX1508.h>
#include <L298N.h>

#define BEEP 14
/*
#define PWM_PINA 10
#define PINA 8
#define PWM_PINB 9
#define PINB 7
#define NUMPWM 1

#define RESOLUTION 255 */

//MX1508 motorA(PWM_PINA,PINA, FAST_DECAY, NUMPWM);
//MX1508 motorB(PWM_PINB,PINB, FAST_DECAY, NUMPWM);
L298N drive;


volatile int pwmA = 0;
volatile int pwmB = 0;
bool forwardA = true;
bool forwardB = true;
volatile bool driveOn = false;

int temperatur = 0;


volatile long driveTimeout = 0;
volatile long driveTimeDiff = 0;

void setup() {
  Serial.begin(115200);
//  motorA.setPWM16(2,RESOLUTION);
//  motorB.setPWM16(2,RESOLUTION);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  clearCommands();
  
  //Temperatur- und Abstandsmessung
  tempDistSetup();
  setEchoPins(16, 5); //16: A2, 5: D5
  timer = millis(); 
}

void loop() {
  if (radio.available()) {
    radio.read(&commands, sizeof(commands));
    commandInterpretation();
  }
  //Serial.println(driveOn);
  if(((millis() - driveTimeDiff) > driveTimeout)) {
    pwmA = 0;
    pwmB = 0;
  }
    drive.setPWM_A(pwmA);
    drive.setPWM_B(pwmB);
	
  //Temperatur- und Abstandsmessung
  
  temperature = dallas(4, 0);
  
  if(millis() - timer >= 100){
  	measureDistance();
  	timer = millis();  
  }
  
  distance = calculateDistance();
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
                        
                      radio.write(&temperature, sizeof(temperature));
                      break;
      }
      case timeToDrive : {
                        uint16_t driveTime = 0;
                        driveTime = (0xFF00 & (commands[i+1] << 8));
                        driveTime |= (0x00FF & commands[i+2]); 
                        driveTimeout = (long)driveTime;
                        driveTimeDiff = millis();
                        Serial.println(driveTimeout);
                        break;
      }
      default :  {      /* pwmA = 0;
                      pwmB = 0;
                      forwardA = true;
                      forwardB = true;
                      driveOn = false; */
                      
                      break; 
      }
    }
  }
  clearCommands();
}
