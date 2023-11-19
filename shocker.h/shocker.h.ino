// shocker.h

#ifndef SHOCKER_H
#define SHOCKER_H

#include "Arduino.h"  // Include necessary libraries

class Shocker () {
private:
    const int chargePin = 8;
    const int dischargePin = 16;

public:
    // constructor (hardware setup)
    Shocker();
    
    void charge(bool on); 

    void discharge(bool on);

    // kill switch 
    void off();
}

#endif // SHOCKER_H
