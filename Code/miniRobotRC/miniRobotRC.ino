//template
#include <PCD8544_SPI.h>
#include <shiftRegButtonLib.h>
#include <myInterrupts.h>

#define CLR_BIT(p,n) ((p) &= ~((1) << (n)))
#define SET_BIT(p,n) ((p) |= (1 << (n)))

#define BL 10         //backlight, Hintergrundbeleuchtung LCD
#define SD_CARD_CS 2  //D2 ist Chip Enable
#define BAT_VOLTAGE A7 //Akkuspannung an A7
#define _OE_LEVEL 7   //D7 fuer Output Enable Pegelwandler
#define BRIGHTNESS OCR1B
//globale Objekte anlegen
volatile PCD8544_SPI lcd;
volatile myInterrupts Timer2;
volatile myInterrupts pwmBL;
volatile shiftRegButton tasten;

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

int pwmA = 0;
int pwmB = 0;
bool forwardA = true;
bool forwardB = true;
bool driveOn = false;
uint16_t driveTimeout = 0;
//#define highByte(x) ( (x) >> (8) ) // keep upper 8 bits
//#define lowByte(x) ( (x) & (0xff) ) // keep lower 8 bits

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(A2, A3); // CE, CSN

const byte address[6] = "00001";

uint8_t commands[32];

const String mainMenu[] = {
  "fahren",                   //0
  "stoppen",               //1
  "manuell fahren",           //2
  "",            //3
  "",          //4
  "",         //5
  "",          //6
  "",          //7  
  "",          //8
  ""           //9
};

const String subMenuEntry0[] = {
  "Zeitdauer",
  "Speed A",
  "Speed B",
  "Starten"  
};
