#include "Steuerung.h"

Steuerung::Steuerung(Joystick* joystick, Motor* left, Motor* right) {
  this -> joystick = joystick;
  this -> left = left;
  this -> right = right;
}

void Steuerung::mapReadingsToMatchPWMValues() {
  (this -> xValue) = map(joystick -> xAxisReading, joystick -> lowestValue, joystick -> highestValue, left -> lowestValue, left -> highestValue);
  (this -> yValue) = map(joystick -> yAxisReading, joystick -> lowestValue, joystick -> highestValue, right -> lowestValue, right -> highestValue);
}

void Steuerung::applyPWMValuesDependingOnReadings() {
  //TODO faktor für die Bedinungen um die abweichung von left zu right auszugleichen
  //float leftFaktor = (left -> highestValue) / 255
  // 
  //vorher aber testen ob nur die this -> vor left und right vergessen wurde.
  if ((abs(this -> xValue) > (this -> joystick -> spaceing)) || (abs(this -> yValue) > (this -> joystick -> spaceing))) {
    if (this -> yValue >= 0) {
      if (this -> xValue >= 0) {
        //+y , +x
        (this -> left -> PWMValue) = this -> yValue;
        (this -> right -> PWMValue) = (this -> yValue) - (this -> xValue);
        if ((this -> xValue) >= (this -> yValue)) {
          (this -> left -> PWMValue) = this -> left -> highestValue;
          (this -> right -> PWMValue) = this -> right -> lowestValue;
        }
      } else {
        //+y , -x
        (this -> left -> PWMValue) = this -> yValue;
        (this -> right -> PWMValue) = (this -> yValue) + (this -> xValue);
        if (abs(this -> xValue) >= (this -> yValue)) {
          (this -> left -> PWMValue) = this -> left -> lowestValue;
          (this -> right -> PWMValue) = this -> right -> highestValue;
        }
      }
    } else {
      if (this -> xValue >= 0) {
        //-y , +x
        (this -> left -> PWMValue) = this -> yValue;
        (this -> right -> PWMValue) = (this -> yValue) + (this -> xValue);
        if (this -> xValue >= abs(this -> yValue)) {
          (this -> left -> PWMValue) = this -> left -> highestValue;
          (this -> right -> PWMValue) = this -> right -> lowestValue;
        }
      } else {
        //-y , -x
        (this -> left -> PWMValue) = this -> yValue;
        (this -> right -> PWMValue) = (this -> yValue) - (this -> xValue);
        if (abs(this -> xValue) >= abs(this -> yValue)) {
          (this -> left -> PWMValue) = this -> left -> lowestValue;
          (this -> right -> PWMValue) = this -> right -> highestValue;
        }
      }
    }
    if (abs(this -> xValue) < (this -> joystick -> spaceing)) {
      (this -> left -> PWMValue) = this -> yValue;
      (this -> right -> PWMValue) = this -> yValue;
    }
  } else {
    (this -> left -> PWMValue) = 0;
    (this -> right -> PWMValue) = 0;
  }

}
void Steuerung::updateValues() {
  joystick -> checkJoystickInput();
  mapReadingsToMatchPWMValues();
  applyPWMValuesDependingOnReadings();
}
