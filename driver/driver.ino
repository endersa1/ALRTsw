#include "vibrator.h"
#include "shocker.h"

enum State {IDLE, VIBRATE, SHOCK};
enum bState {ONE, RAPID, HOLD, REST};

void setup() {
  // put your setup code here, to run once:

  // initialize hardware components
  sensors.setupSensors();
  button.setupButton();
  battery.setupBattery();
  Vibrator vibrator;
  Shocker shocker;
  LEDs.setupLEDs();

}

void loop() {
  // put your main code here, to run repeatedly:

  //read input
  button.readButton();

  //button interrupt, skipping ON function
  if(button.getState() == RAPID) {
    //kill switch
    //turn off kill switch and vibrator, delay (turn off?)
    vibrator.set(0);
    shocker.off();
    delay(30000); //delays 30 seconds
    
  } else if(button.getState() == HOLD) {
    //turn on shocker
    vibrator.set(0);
    shocker.charge(1);
    delay(10); // delay depending on what level shock we want to discharge
    shocker.charge(0);
    shocker.discharge(1);
    delay(5); // time to discharge
    shocker.discharge(0);
  } else {
  //continue reading input
  sensors.readACC();
  sensors.readHRV();
  battery.readCharge();
  
  //process
  sensors.sleepDetectionLoop();
  
  //output
  //vibrator and shocker
  switch(sensors.getState()) { //acount for timing
        case IDLE:
            //set vibrator and shocker to 0
            vibrator.set(0);
            shocker.off();
            break;
        case VIBRATE:
            //set shocker to 0 and implement vibrating
            // shocker set needs to be separated into 
            // charge and discharge so we can control delay
            // in this driver. If it's just one function,
            // we'd have to have delays in the shocker files
            vibrator.set(1);
            shocker.off();
            break;
        case SHOCK:
            //set vibrator to 0 and implement shocking
            vibrator.set(0);
            shocker.charge(1);
            delay(10); // delay depeding on what level shock we want to discharge
            shocker.charge(0);
            shocker.discharge(1);
            delay(5); // time to discharge
            shocker.discharge(0);
            break;
    }

    //LEDS
    switch(battery.getCharge()) { //implement interrupt so they are not always on?

        case one:
            //turn on 1
            //turn off 2 3 4
            LEDs.set(1);
            break;
        case two:
            //turn on 1 2
            //turn off 3 4
            LEDs.set(2);
            break;
        case three:
            //turn on 1 2 3
            //turn off 4
            LEDs.set(3);
            break;
        case four:
            //turn on 1 2 3 4
            LEDs.set(4);
            break;
    }
  }
  

}
