

#include "C:/ALRT/ALRT/button.h/button.h.ino"
#include "C:/ALRT/ALRT/button/button.ino"
#include "C:/ALRT/ALRT/shocker.h/shocker.h.ino"
#include "C:/ALRT/ALRT/shocker/shocker.ino"
#include "C:/ALRT/ALRT/sensors.h/sensors.h.ino"
#include "C:/ALRT/ALRT/sensors/sensors.ino"
#include "C:/ALRT/ALRT/enums.h/enums.h.ino"

const int butPin = 21;
const int LED1_PIN = 1;
const int LED2_PIN = 4;
const int LED3_PIN = 6;
const int LED4_PIN = 5;
const int cshockPin = 7;
const int dshockPin = 2;
const int vibPin = 20;
const int batPin = 0;
const int IMUPin =
const int HRVPin =

//setup button, shocker, sensors
Button button = Button(butPin);
Shocker shocker = Shocker(cshockPin, dshockPin);
Sensors sensors = Sensors(IMUPin, HRVPin);
  
void setup() {
  
  //setup LEDs, vibrator, battery
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  pinMode(vibPin, OUTPUT);
  pinMode(batPin, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  button.readButton();
  
  //button interrupt, skipping ON function
  if(button.getState() == RAPID) {
    
    //kill switch
    //turn off shocker and vibrator, delay (turn off?)
    shocker.set(0);
    setVibrator(0);
    delay(30000); //delays 30 seconds - for debugging only
    
  } else if(button.getState() == HOLD) {
    
     //turn on shocker
     shocker.set(1);
     setVibrator(0);
     
  } else {

  //continue reading input and process
  sensors.readACC();
  sensors.readHRV();
  int charge = getCharge();
  sensors.setState();
  
  //output
  //vibrator and shocker
  switch(sensors.getState()) { //acount for timing
        case IDLE:
            //set vibrator and shocker to 0
            setVibrator(0);
            shocker.set(0);
            break;
        case VIBRATE:
            //set shocker to 0 and implement vibrating
            setVibrator(1);
            shocker.set(0);
            break;
        case SHOCK:
            //set vibrator to 0 and implement shocking
            setVibrator(0);
            shocker.set(1);
            break;
    }

    //LEDS
    if(sensors.isTapped) { //condition for lights to be shown
      LEDs.set(charge);
    }
    
  }

 void setLEDs(int num) {
  switch(num) {
    case 0:
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);
      digitalWrite(LED3_PIN, LOW);
      digitalWrite(LED4_PIN, LOW);
      break;
    case 1:
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, LOW);
      digitalWrite(LED3_PIN, LOW);
      digitalWrite(LED4_PIN, LOW);
      break;
    case 2:
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, HIGH);
      digitalWrite(LED3_PIN, LOW);
      digitalWrite(LED4_PIN, LOW);
   break;
    case 3:
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, HIGH);
      digitalWrite(LED3_PIN, HIGH);
      digitalWrite(LED4_PIN, LOW);
      break;
    case 4:
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, HIGH);
      digitalWrite(LED3_PIN, HIGH);
      digitalWrite(LED4_PIN, HIGH);
      break;
  }
 
}

void setVibrator(int on) {
  if (on) {
    digitalWrite(vibPin, HIGH);
  } else {
    digitalWrite(vibPin, LOW);
  }
}

int getCharge() {
  int charge = digitalRead(batPin);
  // convert to 1 through 4
  return charge;
}
  
