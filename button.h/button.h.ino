// button.h
enum bState {ONE, RAPID, HOLD, REST};

#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"  // Include necessary libraries

class Button () {
  
private:

int pin;
int state;  // HIGH or LOW
int numclicks++;
  unsigned long lastChangeTime;
  unsigned long debounceDelay;
  unsigned long clickThreshold;
  unsigned long holdThreshold;
  bool isPressed;
bState bstate;

public:

Button(int buttonPin, unsigned long debounce = 50, unsigned long clickTime = 500, unsigned long holdTime = 1000)
    : pin(buttonPin), debounceDelay(debounce), clickThreshold(clickTime), holdThreshold(holdTime), isPressed(false) {
    pinMode(pin, INPUT);
    
void setupButton(); //hardware setup
void readButton();
bState getState();

}

#endif // BUTTON_H
