#include "readACC.h"
//put in same folder/arudino project as readACC
//accM = accelerometer
enum State {IDLE, VIBRATE, SHOCK};

State state = IDLE;

void setupSensors() {
  //accelerometer init
  mma.setRange(MMA8451_RANGE_2_G);
}

bool shakeDetected() {
  double X = 0;
  double Y = 0;
  double Z = 0;
  
  // average the accel data of 10 instances - change to account for class memory
  for(int i = 0; i < 10; i++){
	  mma.getEvent(&event);
    X += event.acceleration.x;
    Y += event.acceleration.y;
    Z += event.acceleration.z;
  }

  X = X / 10;
  Y = Y / 10;
  Z = Z / 10;
  totalAccel = sqrt(X*X + Y*Y + Z*Z);
 
  //  Roll threshold value? Needs to be tested 
  ROLL_THRESHOLD = 30;

  if (totalAccel > ROLL_THRESHOLD) { return true }
  else { return false }
}
// source: https://learn.adafruit.com/circuit-playground-d6-dice/shake-detect

void sleepDetectionLoop() {
    mma.read();
    // Not sure if this is in the right place
    string sleepSate = Serial.readString(); //int?
    // will have to get this from the user somehow (bluetooth connection?)
    // string config;

    switch(state) {
        case IDLE:
          // add config condition later 
          if(sleepState)
            state = VIBRATE;
          break;

        case VIBRATE:
          if(shakeDetected()){ state = IDLE; }
          else { state = SHOCK;}
          break;

        case SHOCK:
          if(shakeDetected) { state = IDLE; }  
          break;
    }
}

State getState() {
  return state;
}
