#ifndef __JOYSTICK__
#define __JOYSTICK__

#include "Motor.h"

class Joystick {
    // Pin belegungen
  private:
    uint16_t x_pin; // Pin Nummer an dem der X-output des Joysticks angebunden ist.
    uint16_t y_pin; // Pin Nummer an dem der X-output des Joysticks angebunden ist.
  public:
    int16_t lowestValue;
    int16_t highestValue;
    uint16_t spaceing; // Abstand vom mittelpunkt um zappeln zu verhindern.
    int16_t xAxisReading;
    int16_t yAxisReading;

  public:
    Joystick(uint16_t x_pin, uint16_t y_pin, int16_t lowestValue, int16_t highestValue, uint16_t spaceing);
    void checkJoystickInput();
};
#endif
