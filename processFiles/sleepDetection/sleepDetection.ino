#inlcude "readACC.h"
//put in same folder/arudino project as readACC
//accM = accelerometer
enum State {IDLE, VIBRATE, SHOCK};

State state = IDLE;

void setup() {
  // hardware stuff 
  
  //accelerometer init
  mma.setRange(MMA8451_RANGE_2_G);
}

bool shakeDetected() {
  double X = 0;
  double Y = 0;
  double Z = 0;
  
  // average the accel data of 10 instances 
  for(int i = 0; i < 10; i++){
    accelData data = readACC();
    X += dat.X;
    Y += dat.Y;
    Z +=  dat.Z;/      delay(1);
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

void loop() {
	//read accM
	mma.read();
	mma.getEvent(&event);
	dat.X = event.acceleration.x;
	dat.Y = event.acceleration.y;
	dat.Z = event.acceleration.z;

    switch(state) {
        case IDLE:
        // if(user is falling asleep && band is not in cofig ) ---------use python algorithm
        //      state = VIBRATE

            break;

        case VIBRATE:
        // vibrate (hardware)
        // delay(10000); -> 10000 milliseconds = 10 seconds
        // if(shakeDetected())
        //     state = IDLE
        // else
        //     state = SHOCK

            break;
        case SHOCK:
        // shock (hardware)
        // delay(10000); -> 10000 milliseconds = 10 seconds
        // if(shakeDetected)
        //     state = IDLE
            break;
    }
}