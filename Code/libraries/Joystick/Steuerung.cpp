#include "Steuerung.h"

Steuerung::Steuerung(Joystick* joystick, Motor* left, Motor* right) {
  this -> joystick = joystick;
  this -> left = left;
  this -> right = right;
}

void Steuerung::mapReadingsToMatchPWMValues() {
  (this -> xValue) = map(joystick -> xAxisReading, joystick -> lowestValue, joystick -> highestValue, left -> lowestValue, left -> highestValue);
  (this -> yValue) = map(joystick -> yAxisReading, joystick -> lowestValue, joystick -> highestValue, right -> highestValue, right -> lowestValue);
}

void Steuerung::applyPWMValuesDependingOnReadings() {
  if ((abs(this -> xValue) > (joystick -> spaceing)) || (abs(this -> yValue) > (joystick -> spaceing))) {
    if (this -> yValue >= 0) {
      if (this -> xValue >= 0) {
        //+y , +x
        (left -> PWMValue) = this -> yValue;
        (right -> PWMValue) = (this -> yValue) - (this -> xValue);
        if ((this -> xValue) >= (this -> yValue)) {
          (left -> PWMValue) = left -> highestValue;
          (right -> PWMValue) = right -> lowestValue;
        }
      } else {
        //+y , -x
        (left -> PWMValue) = this -> yValue;
        (right -> PWMValue) = (this -> yValue) + (this -> xValue);
        if (abs(this -> xValue) >= (this -> yValue)) {
          (left -> PWMValue) = left -> lowestValue;
          (right -> PWMValue) = right -> highestValue;
        }
      }
    } else {
      if (this -> xValue >= 0) {
        //-y , +x
        (left -> PWMValue) = this -> yValue;
        (right -> PWMValue) = (this -> yValue) + (this -> xValue);
        if (this -> xValue >= abs(this -> yValue)) {
          (left -> PWMValue) = left -> highestValue;
          (right -> PWMValue) = right -> lowestValue;
        }
      } else {
        //-y , -x
        (left -> PWMValue) = this -> yValue;
        (right -> PWMValue) = (this -> yValue) - (this -> xValue);
        if (abs(this -> xValue) >= abs(this -> yValue)) {
          (left -> PWMValue) = left -> lowestValue;
          (right -> PWMValue) = right -> highestValue;
        }
      }
    }
    if (abs(this -> xValue) < (joystick -> spaceing)) {
      (left -> PWMValue) = this -> yValue;
      (right -> PWMValue) = this -> yValue;
    }
  } else {
    (left -> PWMValue) = 0;
    (right -> PWMValue) = 0;
  }

}
void Steuerung::updateValues() {
  joystick -> checkJoystickInput();
  mapReadingsToMatchPWMValues();
  applyPWMValuesDependingOnReadings();
}
