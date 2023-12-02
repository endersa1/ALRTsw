#include <Arduino.h>
#include "NeuralNetwork.h"
#include "sensors.h"
#include "enums.h"
#ifndef DEBUG
#define DEBUG 1
#endif

const int shockPin;


Sensors sensor;

void setup()
{
  //idk, not much to put hear
}

void loop()
{
  //guard clause for button
  if (sensor.isTapped()) sensor.setState(IDLE); //idr what the button was supposed to do tbh
  else sensor.updateState();
  if (sensor.getState() == SHOCK)
  {
    pinMode(shockPin, HIGH); //"so you have chosen death"
  }
  //etc...
}