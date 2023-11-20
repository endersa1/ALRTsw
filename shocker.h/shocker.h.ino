// shocker.h

#ifndef SHOCKER_H
#define SHOCKER_H

#include "Arduino.h"  // Include necessary libraries

class Shocker () {
private:

    const int chargePin;
    const int dischargePin;
    int state = 0; // 0 off 1 charging 
    unsigned long chargeStartTime;
    unsigned long chargeTime = 10;
    unsigned long dischargeTime = 5;

public:

    Shocker(int cshockPin, int dshockPin, int shockPower) 
    : chargePin(cshockPin), dischargePin(dsockPin) { 
        pinMode(chargePin, OUTPUT); 
        pinMode(dischargePin, OUTPUT);  
        // some code to convert shock power to charge time
        charge time =
    }
    

    void set(bool on); // 1 on 0 off

}

#endif // SHOCKER_H
