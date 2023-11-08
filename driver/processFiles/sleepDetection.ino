

11 of 24
Some Code + Writeup
Inbox

Meredith Doan
Attachments
Nov 6, 2023, 3:46 PM (2 days ago)
to me

Hello!

I've attached two files below. Here's what I have for each so far.

sleepDetection.cpp: This is the general structure for the state machine. In this code, you'll find the setup function (which is currently empty, as I'm not sure about the hardware connections), the shake detection function, and the main loop which switches between the three different states. A lot of this is pseudo code to be filled in later. 

readACC.cpp: This contains the Arduino connection to the accelerometer and the accelerometer data acquisition. This is a revised version of the Arduino example sketch for the MMA8451 from the parts list. 

Both of these files follow the structure of an Arduino sketch: a setup function that establishes hardware connections and a loop function that performs the actual tasks. I'm not really sure how this structure will scale with our complex program, and I'm not sure how data will be passed between these programs (or if they will just be condensed into one). Let me know if you have any questions, or if you have any input on the structuring. 

Warm Regards, 
Meredith Doan


--
Meredith Doan
She/Her/Hers
Undergraduate Computer Engineering Student
College of Engineering | The University of Michigan 

2
 Attachments
  •  Scanned by Gmail
Thanks, I'll take a look.Thanks, I'll check them out.This is great, thank you so much!
enum State {IDLE, VIBRATE, SHOCK};

State state = IDLE;

void setup() {
  // hardware stuff 
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

    switch(state) {
        case IDLE:
        // if(user is falling asleep && band is not in cofig )
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
