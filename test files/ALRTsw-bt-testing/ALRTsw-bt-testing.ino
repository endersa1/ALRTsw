
#include "button.h"
#include "shocker.h"
#include "sensors.h"
#include "enums.h"

const int butPin = 21;
const int LED1_PIN = 1;
const int LED2_PIN = 4;
const int LED3_PIN = 6;
const int LED4_PIN = 5;
const int cshockPin = 7;
const int dshockPin = 2;
const int vibPin = 20;
const int batPin = 0;
//const int SDAPin = 8;
//const int SCLPin = 9;
unsigned long lastLEDChangeTime = millis();

//setup button, shocker, sensors
Button button = Button(butPin);
//Shocker shocker = Shocker(cshockPin, dshockPin);
Sensors sensors = Sensors();


void setupBluetooth() {

}
  
void setup() {
  
  //setup LEDs, vibrator, battery
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  pinMode(vibPin, OUTPUT);
  pinMode(batPin, INPUT);

  Serial.begin(115200);

  setupBluetooth();
  
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

int getCharge() { //needs testing
  int charge = digitalRead(batPin);
  // convert to 1 through 4
  return charge;
}

void loop() {

  ////////////// BLUETOOTH /////////////////////


  //int newRestTime = 0;
  //sensors.updateRestTime(newRestTime);



 //////////////////////////////////////////////
  
  //read button input
  button.readButton();

  //turn off LEDs after 5 seconds
  if(lastLEDChangeTime - millis() > 5000) {
    setLEDs(0);
  }
  
  //button interrupt, skipping ON function
  if(button.getState() == RAPID) {
    
    //kill switch
    //turn off shocker and vibrator, delay (turn off?)
    //shocker.set(0);
    Serial.println("shock off");
    setVibrator(1);
    delay(30000); //delays 30 seconds - for debugging only
    
  } else if(button.getState() == HOLD) {
    
     //turn on shocker
     //shocker.set(1);
     Serial.println("shock on");
     setVibrator(0);
     
  } else {

  //continue reading input and process
  int charge = getCharge();
  sensors.setState();
  
  //output
  //vibrator and shocker
  switch(sensors.getState()) {
        case IDLE:
            //set vibrator and shocker to 0
            setVibrator(0);
            //shocker.set(0);
            Serial.println("shock off");
            break;
        case VIBRATE:
            //set shocker to 0 and implement vibrating
            setVibrator(1);
            //shocker.set(0);
            Serial.println("shock off");
            break;
        case SHOCK:
            //set vibrator to 0 and implement shocking
            setVibrator(0);
            //shocker.set(1);
            Serial.println("shock on");
            break;
    }

    //LEDS
    if(sensors.isTapped()) { //condition for lights to be shown
      setLEDs(charge);
      lastLEDChangeTime = millis();
    }
    
  }
}
