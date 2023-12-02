// button.h


#ifndef SENSORS_H
#define SENSORS_H

#include "Arduino.h"  // Include necessary libraries
#include "enums.h"
#include <vector>
#include <Wire.h>
#include "Adafruit_MMA8451.h"
#include <Adafruit_Sensor.h>
#include "NeuralNetwork.h"



using std::vector;

class Sensors {

private:

Adafruit_MMA8451 mma = Adafruit_MMA8451();

NeuralNetwork *nn;

const int aPin;
const int hPin;
State state = IDLE; //IDLE VIBRATE or SHOCK
unsigned long vibrateDuration = 4000;
unsigned long restTime = 7000;
unsigned long startVibrate;
unsigned long lastShock;
bool live;//variable for if NN has enough inputs to run
vector<double> Xdata; // in chronological order
vector<double> Ydata;
vector<double> Zdata;
vector<double> hrReadings;
vector<float> sleepReadings; //last 5 outputs of sleep detection alg

public:

Sensors(int IMUPin, int HRVPin) : aPin(IMUPin), hPin(HRVPin) 
{nn = new NeuralNetwork(); pinMode(aPin, INPUT); pinMode(hPin, INPUT); }
bool shakeDetected();
void updateState();
void setState(State province);
State getState();
bool isTapped();
  
};
#endif
//SENSORS_H