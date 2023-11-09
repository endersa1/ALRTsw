enum State {IDLE, VIBRATE, SHOCK};
enum bState {ONE, RAPID, HOLD};

void setup() {
  // put your setup code here, to run once:

  // initialize hardware components
  sensors.setUpSensors();
  button.setUpButton();

}

void loop() {
  // put your main code here, to run repeatedly:

  //readInput
  sensors.readACC();
  sensors.readHRV();
  
  //process
  sensors.sleepDetectionLoop();
  button.handleButton();
  
  //output

  //vibrator and shocker
  switch(sensors.getState()) { //acount for timing
        case IDLE:

            //set vibrator and shocker to 0

            break;

        case VIBRATE:

            //set shocker to 0 and implement vibrating

            break;
            
        case SHOCK:

            //set vibrator to 0 and implement shocking

            break;
    }

    //LEDS

    switch(battery.getCharge()) { //implement interrupt so they are not always on?

        case one:

            //turn on 1
            //turn off 2 3 4

            break;

        case two:

            //turn on 1 2
            //turn off 3 4

            break;
            
        case three:

            //turn on 1 2 3
            //turn off 4

            break;
            
        case four:

            //turn on 1 2 3 4

            break;
    }

}
