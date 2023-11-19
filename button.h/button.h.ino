// button.h


#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"  // Include necessary libraries
#include "C:/ALRT/ALRT/enums.h/enums.h.ino"

class Button {
  
private:

int pin;
int state;  // HIGH or LOW
int numclicks = 0;
unsigned long lastChangeTime;
unsigned long debounceDelay = 50;
unsigned long clickThreshold = 500;
unsigned long holdThreshold = 1000;
bool isPressed;
bState bstate; // ONE, RAPID, HOLD, REST

public:

Button(int buttonPin) : pin(buttonPin), isPressed(false), bstate(REST), lastChangeTime(millis()) { pinMode(pin, INPUT); }
void readButton();
bState getState();

};


#endif // BUTTON_H
