// button.h


#ifndef SENSORS_H
#define SENSORS_H

#include "Arduino.h"  // Include necessary libraries
#include "C:/ALRT/ALRT/enums.h/enums.h.ino"

class Sensors {

private:

const int aPin;
const int hPin;
State state = IDLE; //IDLE VIBRATE or SHOCK
unsigned long vibrateDuration = 4000;
unsigned long restTime = 7000;
unsigned long startVibrate;
unsigned long lastShock;

Vector<double> Xdata; // in chronological order
Vector<double> Ydata;
Vector<double> Zdata;

public:

Sensors(int IMUPin, int HRVPin) : aPin(IMUPin), hPin(HRVPin) { pinMode(aPin, INPUT); pinMode(hPin, INPUT); }
void setState();
State getState();
bool isTapped();
  
}
#endif // SENSORS_H
