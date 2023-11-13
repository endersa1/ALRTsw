enum State {IDLE, VIBRATE, SHOCK};
enum bState {ONE, RAPID, HOLD, REST};

void setup() {
  // put your setup code here, to run once:

  // initialize hardware components
  sensors.setupSensors();
  button.setupButton();
  battery.setupBattery();
  vibrator.setupVibrator();
  shocker.setupShocker();
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
    shocker.set(0);
    delay(30000); //delays 30 seconds
    
  } else if(button.getState() == HOLD) {
     //turn on shocker
     vibrator.set(0);
     shocker.set(1);
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
            shocker.charge(0);
            shocker.discharge(0);
            break;
        case VIBRATE:
            //set shocker to 0 and implement vibrating
            // shocker set should be separated into 
            // charge and discharge so we can control delay
            vibrator.set(1);
            shocker.charge(0);
            shocker.discharge(0);
            break;
        case SHOCK:
            //set vibrator to 0 and implement shocking
            vibrator.set(0);
            shocker.charge(1);
            delay(10000); // delay depeding on what level shock we want to discharge
            shocker.charge(0);
            shocker.discharge(1);
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
