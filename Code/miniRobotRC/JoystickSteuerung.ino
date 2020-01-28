#include <Steuerung.h>
//Informationen Joystick

Joystick *joystick;
const uint16_t xAxisPin = 5;
const uint16_t yAxisPin = 4;
const int16_t lowestJoystickValue = 0;
const int16_t highestJoystickValue = 511;
const int16_t spaceing = 50;

//Informationen linker Motor
Motor *left;
const int16_t lowestPWMValueLeftMotor = -255;
const int16_t highestPWMValueLeftMotor = 255;

//Informationen rechter Motor
Motor *right;
const int16_t lowestPWMValueRightMotor = -255;
const int16_t highestPWMValueRightMotor = 255;


Steuerung *steuerung;

void joystickInit() {
  
    joystick = new Joystick(xAxisPin, yAxisPin, lowestJoystickValue, highestJoystickValue, spaceing);
    left = new Motor(lowestPWMValueLeftMotor, highestPWMValueLeftMotor);
    right = new Motor(lowestPWMValueRightMotor, highestPWMValueRightMotor);
    steuerung = new Steuerung(joystick, left, right);
    //Serial.begin(9600);
  }

  void joystickSteuerung() {
    //Only updates if joystick is moved
    steuerung -> updateValues();

    //DEBUG
    Serial.print("Left motor PWMValue: ");
    Serial.println(left -> PWMValue);
    Serial.print("Right motor PWMValue: ");
    Serial.println(right -> PWMValue);
    
    //SendValues
    send();
  }

  void send(){
        commands[0] = speedA;
        commands[1] = highByte(left -> PWMValue);
        commands[2] = lowByte(left -> PWMValue);
        commands[3] = speedB;
        commands[4] = highByte(right -> PWMValue);
        commands[5] = lowByte(right -> PWMValue);
        commands[6] = timeToDrive;
        commands[7] = highByte(driveTimeout);
        commands[8] = lowByte(driveTimeout);
        commands[9] = goDrive;
        radio.write(&commands, sizeof(commands));
  }
