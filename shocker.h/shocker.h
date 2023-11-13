#include "Arduino.h"

class shocker {
    public:

    void setupShocker {
        // shock chg
        pinMode(8, OUTPUT);
        // shock dls 
        pinMode(16, OUTPUT);
    }

    void charge(bool on) {
        if(on){
            digitalWrite(8, HIGH);
        }
        else { 
            digitalWrite(8, LOW);
        }

    }

    void discharge(bool on) {
        if(on){
            digitalWrite(16, HIGH);
        }
        else { 
            digitalWrite(16, LOW);
        }
    }
};
