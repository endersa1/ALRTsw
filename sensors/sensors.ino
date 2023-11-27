#include "C:/ALRT/ALRT/sensors.h/sensors.h.ino"
#include "C:/ALRT/ALRT/enums.h/enums.h.ino"
#include "Arduino.h"  // Include necessary libraries


void Sensors::setState() {

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
            startVibrate = millis(); 
          } else { 
            state = IDLE; 
          }
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

bool Sensors::isTapped() { //needs tuning
  bool tap = false;
  
  //detect tap
  int windowSize = 10;  // Adjust the window size based on your application
  if (Xdata.size() < windowSize) { //error handling for small vectors
    return false;
  }
  double xAvg, yAvg, zAvg;
  int threshold = 1000;  // Adjust the threshold based on your sensor and sensitivity

  // Update averages
  double sum = 0;
  for (int i = Xdata.size() - windowSize; i < Xdata.size(); ++i) {
    sum += Xdata[i];
  }
  xAvg sum / windowSize;
  sum = 0;
  for (int i = Ydata.size() - windowSize; i < Ydata.size(); ++i) {
    sum += Ydata[i];
  }
  yAvg = sum / windowSize;
  sum = 0;
  for (int i = Zdata.size() - windowSize; i < Zdata.size(); ++i) {
    sum += Zdata[i];
  }
  zAvg = sum / windowSize;

  // Detect tap on X-axis
  if (abs(Xdata[Xdata.size() - 1] - xAvg) > threshold) {
    tap = true;
  }

  // Detect tap on Y-axis
  if (abs(Ydata[Ydata.size() - 1] - yAvg) > threshold) {
    tap = true;
  }

  // Detect tap on Z-axis
  if (abs(Zdata[Zdata.size() - 1] - zAvg) > threshold) {
    tap = true;
  }

  return tap;
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
