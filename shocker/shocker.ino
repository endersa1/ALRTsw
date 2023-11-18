#include "shocker.h"
#include "Arduino.h"
const int chargePin = 8;
const int dischargePin = 16;

void Shocker::setupShocker() {
  // put your setup code here, to run once:

  Shocker(chargePin, dischargePin);

}

void Shocker::charge(bool on) {
  if(on){
      digitalWrite(chargePin, HIGH);
  }
  else { 
      digitalWrite(chargePin, LOW);
  }

}

void Shocker::discharge(bool on) {
  if(on){
      digitalWrite(dischargePin, HIGH);
  }
  else { 
      digitalWrite(dischargePin, LOW);
  }
}

void Shocker::off() {
  digitalWrite(dischargePin, LOW);
  digitalWrite(chargePin, LOW);
  
}
