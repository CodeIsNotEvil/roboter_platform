#include <PCD8544_SPI.h>
#include <shiftRegButtonLib.h>
#include <myInterrupts.h>

#define CLR_BIT(p,n) ((p) &= ~((1) << (n)))
#define SET_BIT(p,n) ((p) |= (1 << (n)))
//Pinzuordnungen
#define BL 10         //backlight, Hintergrundbeleuchtung LCD
#define SD_CARD_CS 2  //D2 ist Chip Enable
#define BAT_VOLTAGE A7 //Akkuspannung an A7
#define _OE_LEVEL 7   //D7 fuer Output Enable Pegelwandler
#define BRIGHTNESS OCR1B
//globale Objekte anlegen
volatile PCD8544_SPI_FB lcd;
volatile myInterrupts Timer2;
volatile myInterrupts pwmBL;
volatile shiftRegButton tasten;
//LCD
uint8_t renderTime = 0;
#define renderTimeout 100   //es wird alle 100ms gerendert
String lcdLines[6];         //Strings welche alle 100ms ausgegeben werden

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

int16_t pwmA = 0;
int16_t pwmB = 0;
bool forwardA = true;
bool forwardB = true;
bool driveOn = false;
uint16_t driveTimeout = 0;

int16_t distance;
int16_t temperature = 0;

//Funk
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(A2, A3); // CE, CSN

const byte address[6] = "00001";

uint8_t commands[32];
