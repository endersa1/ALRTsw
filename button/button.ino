#include "C:/ALRT/ALRT/button.h/button.h.ino"
#include "Arduino.h"
#include "C:/ALRT/ALRT/enums.h/enums.h.ino"

void Button::readButton() {

  int buttonState = digitalRead(pin);

  if (buttonState != state) {
     bstate = ONE;
     state = buttonState;
     isPressed = buttonState;
    /*
      // Debounce
      if (millis() - lastChangeTime > debounceDelay) { //ie not an error / noise
        state = buttonState;
        lastChangeTime = millis();

        if (state == HIGH) {
          // Button pressed
          isPressed = true;
        } else {
          // Button released
          isPressed = false;
          //check for click
          if (millis() - lastChangeTime > clickThreshold) {
            //later - on function here
            //account clicks for rapid clicking
            numclicks++;
            if(numclicks > 3) {
              bstate = RAPID;
            } else {
              bstate = ONE;
            }
          }
        }
      }
      */
  } else {
    //check held
    if (isPressed && millis() - lastChangeTime > holdThreshold) {
      bstate = HOLD;
    } else if (millis() - lastChangeTime > holdThreshold) {
      bstate = REST;
      numclicks = 0;
    }
  }


}

bState Button::getState() {
  return bstate;
}
