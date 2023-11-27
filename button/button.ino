#include "C:/ALRT/ALRT/button.h/button.h.ino"
#include "Arduino.h"
#include "C:/ALRT/ALRT/enums.h/enums.h.ino"

void Button::readButton() {

  int buttonState = digitalRead(pin);

  if (buttonState != state) {

    state = buttonState;
    
    //check for click
    if (state == 0 && millis() - lastChangeTime > clickThreshold) {
      numclicks++;
      //check for rapid clicking 
      if (numclicks > 2) {
          bstate = RAPID;
      } else {
          bstate = ONE;
      }
    } else {
      bstate = bstate;
    }

    lastChangeTime = millis();

      // Debounce
      //if (millis() - lastChangeTime > debounceDelay) { //ie not an error / noise

  } else {

    //check for hold
    if (state == 1 && millis() - lastChangeTime > holdThreshold) {
      bstate = HOLD;
      numclicks = 0;
    } else if (millis() - lastChangeTime > holdThreshold) {
      bstate = REST;
      numclicks = 0;
    } else {
      bstate = bstate;
    }
    
  }
}

bState Button::getState() {
  return bstate;
}
