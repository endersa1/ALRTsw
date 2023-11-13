#include "shocker.h"
#include "Arduino.h"
const int chargePin = 8;
const int dischargePin = 16;

void setupShocker() {
  // put your setup code here, to run once:

  Shocker(chargePin, dischargePin);

}

void set(int i) {
  switch(i) {
    case 0: {
      //turn shocker off completely

      
      break;
    }
    case 1: {
      //turn/keep shocker on

      
      break;
    }
  }

}
