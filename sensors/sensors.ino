#include "C:/ALRT/ALRT/sensors.h/sensors.h.ino"
#include "C:/ALRT/ALRT/enums.h/enums.h.ino"
#include "Arduino.h"  // Include necessary libraries


void Button::setState() {

  //read ACC - add to vectors and clear old data
  mma.read(); //?

  //read HRV

  //sleep detection algorithm
  int sleepy = // 1 yes 0 no

  switch(state) {
        case IDLE:
          // add config condition later 
          if(sleepy && millis() - lastShock > restTime) {
            state = VIBRATE;
            startVibrate = millis(); }
          else { state = IDLE; }
          break;

        case VIBRATE:
          if(shakeDetected()){ state = IDLE; }
          else if ( millis() - startVibrate > vibrateDuration) { state = SHOCK;}
          else { state = VIBRATE; }
          break;

        case SHOCK:
          if(shakeDetected()) { state = IDLE; }  
          else { state = SHOCK; lastShock = millis(); }
          break;
    }
  
  
}

bool shakeDetected() {
  double X = 0;
  double Y = 0;
  double Z = 0;
  
  // average the accel data of 10 instances
  for(int i = 0; i < min(10, Xdata.size()); i++){
    X += Xdata[Xdata.size()-1-i];
    Y += Ydata[Ydata.size()-1-i];
    Z += Zdata[Zdata.size()-1-i];
  }

  X = X / min(10, Xdata.size());
  Y = Y / min(10, Xdata.size());
  Z = Z / min(10, Xdata.size());
  double totalAccel = sqrt(X*X + Y*Y + Z*Z);
 
  //  Roll threshold value? Needs to be tested 
  int ROLL_THRESHOLD = 30;

  if (totalAccel > ROLL_THRESHOLD) { return true; }
  else { return false; }
}
// source: https://learn.adafruit.com/circuit-playground-d6-dice/shake-detect


State Sensors::getState() {
  return state;
}
