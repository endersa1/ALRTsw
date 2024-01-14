// button.h


#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"  // Include necessary libraries
#include "enums.h"

class Button {
  
private:

int pin;
int state;  // HIGH or LOW
int numclicks = 0;
unsigned long lastChangeTime;
unsigned long debounceDelay = 30;
unsigned long clickThreshold = 50;
unsigned long holdThreshold = 1000;
bState bstate; // ONE, RAPID, HOLD, REST

public:

Button(int buttonPin) : pin(buttonPin), bstate(REST), state(0), lastChangeTime(millis()) { pinMode(pin, INPUT); }
void readButton();
bState getState();

};


#endif // BUTTON_H
