#include "vibrator.h"
#include "Arduino.h"


Vibrator::Vibrator() {
    pinMode(vibPin, OUTPUT);
}

void Vibrator::set(bool on) {
    if(on){
        digitalWrite(vibPin, HIGH);
    }
    else{
        digitalWrite(vibPin, LOW);
    }
}