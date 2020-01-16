#ifndef __STEUERUNG__
#define __STEUERUNG__

#include "Motor.h"
#include "Joystick.h"

class Steuerung {
  private:
    Joystick* joystick;
    Motor* left;
    Motor* right;
    int16_t xValue;
    int16_t yValue;

  public:
    Steuerung(Joystick* joystick, Motor* left, Motor* right);
    void updateValues();

  private:
    void mapReadingsToMatchPWMValues();
    void applyPWMValuesDependingOnReadings();


};
#endif
