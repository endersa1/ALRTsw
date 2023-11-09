// button.h

#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"  // Include necessary libraries

class Button () {
  
private:
bState state;

public:
void setupButton(); //hardware setup
void readButton();
void handleButton();
bState getState();

}

#endif // BUTTON_H
