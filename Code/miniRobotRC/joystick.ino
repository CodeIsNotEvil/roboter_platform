#define xPin A5
#define yPin A6
#define leftMax 255//215
#define leftMin -255//-100
#define rightMax 255
#define rightMin -255

volatile int16_t xValue = 0;
volatile int16_t yValue = 0;
volatile int16_t leftPWM = 0;
volatile int16_t rightPWM = 0;

const int16_t deadZone = 40;

void motorMapping() {
  static long temp = millis();
  koordinaten(analogRead(xPin), analogRead(yPin));
  motorPWM();
  
  pwmB = map(leftPWM, -255,255,leftMin,leftMax);
  pwmA = map(rightPWM, -255,255,rightMin,rightMax);
  if((millis() - temp) > 100) {
 //   lcd.clear();
 //   lcd.println("Links: ");
    lcdLines[0] = "Links: " + String(pwmB, DEC);
 //   lcd.println(pwmB);
 //   lcd.gotoXY(0,2);
 //   lcd.println("Rechts: ");
    lcdLines[1] = "Rechts: " + String(pwmA, DEC);
 //  lcd.println(pwmA);
  }

  senden();
}

void senden() {
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
		    commands[10] = getDistance;
        radio.write(&commands, sizeof(commands));
}

void koordinaten(uint16_t x, uint16_t y) {
  //9-bit reichen, der ADC schafft bestenfalls 8-bit praezision
  x = x >> 1;
  y = y >> 1;
  xValue = map(x, 0, 511, -255, 255);
  yValue = map(y, 0, 511, 255, -255);
}

void motorPWM() {
 if((abs(xValue) > deadZone) || (abs(yValue) > deadZone)) {
  if(yValue >= 0) {
    if(xValue >= 0) {
    //+y , +x  
      leftPWM = yValue;
      rightPWM = yValue - xValue;
      if(xValue >= yValue) {
        leftPWM = 255;
        rightPWM = -255;
      }
    } else {
      //+y , -x
        leftPWM = yValue;
        rightPWM = yValue + xValue;
        if(abs(xValue) >= yValue) {
          leftPWM = -255;
          rightPWM = 255;
        }
    }
  } else {
      if(xValue >= 0) {
      //-y , +x  
        leftPWM = yValue;
        rightPWM = yValue + xValue;
        if(xValue >= abs(yValue)) {
          leftPWM = 255;
          rightPWM = -255;
        }
      } else {
        //-y , -x
          leftPWM = yValue;
          rightPWM = yValue - xValue;
          if(abs(xValue) >= abs(yValue)) {
            leftPWM = -255;
            rightPWM = 255;
          }
      }
  }
  if(abs(xValue) < deadZone) {
    leftPWM = yValue;
    rightPWM = yValue;
  }
 } else {
    leftPWM = 0;
    rightPWM = 0;
 }
}
