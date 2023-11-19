#include "vibrator.h"
#include "Arduino.h"


Vibrator(){
    pinMode(vibPin, OUTPUT);
}

void set(bool on) {
    if(on){
        digitalWrite(vibPin, HIGH);
    }
    else{
        digitalWrite(vibPin, LOW);
    }
}