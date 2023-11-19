#include "C:/ALRT/ALRT/shocker.h/shocker.h.ino"
#include "Arduino.h"

void Shocker::set(bool on) {
  if (on == 0) {
    digitalWrite(dischargePin, LOW);
    digitalWrite(chargePin, LOW);
    state = 0;
    return;
  }
  if (on != state) { //turns on for first time
      //start charging 
      state = 1;
      chargeStartTime = millis();
  } else if (millis() - chargeStartTime > chargeTime) { //time to discharge 
      state = 0;
      digitalWrite(dischargePin, HIGH);
      delay(dischargeTime); //if this is low enough its ok to keep it here
      digitalWrite(dischargePin, LOW);
  }
}
