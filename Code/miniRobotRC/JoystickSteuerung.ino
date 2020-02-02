#include <Steuerung.h>
//Informationen Joystick

Joystick *joystick;
const uint16_t xAxisPin = 5;
const uint16_t yAxisPin = 6;
const int16_t lowestJoystickValue = 0;
const int16_t highestJoystickValue = 511;
const int16_t spaceing = 60;

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
    
    //Show Values On LCD
    showValuesOnLCD();
    
    //SendValues
    send();
  }

  void showValuesOnLCD(){
    lcd.clear();
    lcd.print("WithLib");
    lcd.gotoXY(0,2);
    lcd.print("LeftPWM: ");
    lcd.print(left -> PWMValue);
    lcd.gotoXY(0,4);
    lcd.print("RightPWM: ");
    lcd.print(right -> PWMValue);
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
        commands[10] = getTemp;
        commands[11] = highByte(temperature);
        commands[12] = lowByte(temperature);
        commands[13] = getTemp;
        commands[14] = highByte(distance);
        commands[15] = lowByte(distance);
        radio.write(&commands, sizeof(commands));
  }
