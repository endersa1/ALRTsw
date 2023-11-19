#include "shocker.h"
#include "Arduino.h"

Shocker::Shocker() {
  pinMode(chargePin, OUTPUT); 
  pinMode(dischargePin, OUTPUT);
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
