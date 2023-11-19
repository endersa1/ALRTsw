#ifndef VIBRATOR_H
#define VIBRATOR_H

#include "Arduino.h"

class Vibrator {
    private: 
        const int vibPin = 12;
    
    public:
        // constructor 
        Vibrator();

        // turn vibrator on and off
        void set(bool on);

};

#endif // VIBRATOR_H