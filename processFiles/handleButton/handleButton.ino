#include "button.h"
#include "Arduino.h"
enum bState {ONE, RAPID, HOLD, REST};
const int buttonPin = 13;

void setupButton() {

  Button(buttonPin);
  
}

void readButton() {

  int buttonState = digitalRead(buttonPin);

  if (buttonState != state) {
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
            }
          }
        }
      }
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

bState getState() {
  return bstate;
}
