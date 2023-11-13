// shocker.h

#ifndef SHOCKER_H
#define SHOCKER_H

#include "Arduino.h"  // Include necessary libraries

class Shocker () {
  
private:

int chargePin;
int dischargePin;

public:

Shocker(int cPin, dPin)
    : chargePin(cPin), dischargePin(dPin) {
    pinMode(chargePin, OUTPUT); pinMode(dischargePin, OUTPUT);}
    
void setupShocker(); //hardware setup
void set();

}

#endif // SHOCKER_H
