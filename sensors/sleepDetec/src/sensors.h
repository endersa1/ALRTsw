// button.h


#ifndef SENSORS_H
#define SENSORS_H
#include "Arduino.h"  // Include necessary libraries
#include "enums.h"
#include <vector>
#include <Wire.h>
#include <MAX30105.h>
#include <MPU6050.h>
#include "NeuralNetwork.h"
#include "heartRate.h"



using std::vector;

class Sensors {

private:

NeuralNetwork *nn;

MAX30105 particleSensor;
MPU6050 mpu;
State state = IDLE; //IDLE VIBRATE or SHOCK
unsigned long vibrateDuration = 4000;
unsigned long restTime = 7000;
unsigned long startVibrate;
unsigned long lastShock;
uint32_t lastHRVchange = millis();
int bpm = 0;
int num = 0;
bool live; //variable for if NN has enough inputs to run
vector<float> Xdata; // in chronological order
vector<float> Ydata;
vector<float> Zdata;
vector<float> hrReadings;
vector<float> sleepReadings; //last 5 outputs of sleep detection alg

public:

Sensors() {
    nn = new NeuralNetwork(); 
    Wire.begin();
    mpu.initialize();
    particleSensor.begin();
    particleSensor.setup();
}
bool shakeDetected();
bool isTapped();
void setState();
State getState();
bool calculateBPM(int beat);
  
};

#endif
//SENSORS_H