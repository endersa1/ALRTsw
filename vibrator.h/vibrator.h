#include "Arduino.h"

class vibrator {
    public:

    void setupVibrator {
        pinMode(12, OUTPUT);
    }

    void set(bool on) {
        if(on){
            digitalWrite(12, HIGH);
        }
        else{
            digitalWrite(12, LOW);
        }
    }

};