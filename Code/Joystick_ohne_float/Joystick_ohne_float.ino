#define xPin A5
#define yPin A6
int16_t xValue = 0;
int16_t yValue = 0;
int16_t leftPWM = 0;
int16_t rightPWM = 0;

const int16_t deadZone = 10;

void setup() {
  Serial.begin(115200);
}

void loop() {
  koordinaten(analogRead(xPin), analogRead(yPin));
  motorPWM();
  Serial.print("X: ");
  Serial.println(xValue);
  Serial.print("Y: ");
  Serial.println(yValue);
  Serial.print("links: ");
  Serial.println(leftPWM);
  Serial.print("rechts: ");
  Serial.println(rightPWM);

  delay(200);

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
