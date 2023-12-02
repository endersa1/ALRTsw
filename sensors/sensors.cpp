#include "sensors.h"
#include "enums.h"
#include <Arduino.h>  // Include necessary libraries
//TODO: XYZ DATA ARE NOT UPDATED!! (seemingly)
#include <vector>
const int stack = 60;
double win[stack];
std::vector<float> popBackFixed(int maxLen, std::vector<float> vec, float data)
{
    /*
    Adds item to end of vector, but removes first item if it would get longer than maxLen
    TODO: logic for vectors more than 1 item longer than maxLen
    */
  if (vec.size() < maxLen) {vec.push_back(data);}
  else {vec.erase(vec.begin()); vec.emplace(vec.end(), data);}
  return vec;
}
int most(std::vector<float> readings)
{
  //returns 1 if 4 of last 5 readins is 1
  int count = 0;
  for (int i = 0;i<5;i++) if(readings[i] >= 0.5) count++;
  if (count >= 4) return 1;
  return 0;
}
double magnitude(double x, double y, double z)
{
  return sqrt(x*x + y*y + z*z);
}
void normByTwos(int n, double win[], NeuralNetwork * NN)
{
  double mnHR = INT_MAX;
  double mnACC = INT_MAX;
  double mxHR = INT_MIN;
  double mxACC = INT_MIN;
  for (int i = 0; i<n;i++)
  {
    if (i%2 == 1){
      if (win[i] > mxHR) mxHR = win[i];
      if (win[i] < mnHR) mnHR = win[i];
    }
    else{
      if (win[i] > mxACC) mxACC = win[i];
      if (win[i] < mnACC) mnACC = win[i];}
  }
  double dACC = mxACC-mnACC;
  double dHR = mxHR-mnHR;
  
  for (int i = 0; i<n; i++)
  {
    if(i%2==1) NN->getInputBuffer()[i] = (float)(win[i]-mnHR)/(dHR);
    else NN->getInputBuffer()[i] = (float)(win[i]-mnACC)/(dACC);
  }
}
void loadReadings(NeuralNetwork * nn, vector<double> yData, vector<double> xData, vector<double> zData, vector<double> hr)
{//OPTIMIZATION: SOTRE MAGS IN OTHER VEC (assert len==stack) TO SAVE COMP STIME
  if (yData.size() != stack/2) return; //same for all other vecs
  for (int i = 0; i< stack;i++)
  {
    if (i%2==0) win[i] = magnitude(yData[i], xData[i], zData[i]);
    else win[i] = hr[i];
  }
  normByTwos(stack, win, nn); //normalizes data then loads onto NN's input buffer

}
void Sensors::updateState() {

  //read ACC - add to vectors and clear old data
  mma.read(); //?

  loadReadings(nn, Ydata, Xdata, Zdata, hrReadings);
  //DATA VECTORS ARE OF LENGTH 30 (stack/2) EACH, VEC[0] = OLDEST READING, VEC[VEC.SIZE()-1] = LATEST READING

  sleepReadings = popBackFixed(5, sleepReadings, nn->predict());
	//USE THIS CODE TO UPDATE LAST ITEM IN VECTOR, AND REPLACE FIRST (oldest) WITHOUT CHNAGING LENGTH
  //read HRV

  //sleep detection algorithm
  int sleepy = most(sleepReadings);// 1 yes 0 no

  switch(state) {
        case IDLE:
          // add config condition later 
          if(sleepy && millis() - lastShock > restTime) {
            state = VIBRATE;
            startVibrate = millis(); 
          } else { 
            state = IDLE; 
          }
          break;

        case VIBRATE:
          if(shakeDetected()){ state = IDLE; }
          else if ( millis() - startVibrate > vibrateDuration) { state = SHOCK;}
          else { state = VIBRATE; }
          break;

        case SHOCK:
          if(shakeDetected()) { state = IDLE; }  
          else { state = SHOCK; lastShock = millis(); }
          break;
    }
  
  
}
void Sensors::setState(State province)
{
  state = province;
  //should one man (public setter) has all this power? (indirect access to private variable)
}

bool Sensors::isTapped() { //needs tuning
  bool tap = false;
  
  //detect tap
  int windowSize = 10;  // Adjust the window size based on your application
  if (Xdata.size() < windowSize) { //error handling for small vectors
    return false;
  }
  double xAvg, yAvg, zAvg;
  int threshold = 1000;  // Adjust the threshold based on your sensor and sensitivity

  // Update averages
  double sum = 0;
  for (int i = Xdata.size() - windowSize; i < Xdata.size(); ++i) {
    sum += Xdata[i];
  }
  xAvg = sum / windowSize;
  sum = 0;
  for (int i = Ydata.size() - windowSize; i < Ydata.size(); ++i) {
    sum += Ydata[i];
  }
  yAvg = sum / windowSize;
  sum = 0;
  for (int i = Zdata.size() - windowSize; i < Zdata.size(); ++i) {
    sum += Zdata[i];
  }
  zAvg = sum / windowSize;

  // Detect tap on X-axis
  if (abs(Xdata[Xdata.size() - 1] - xAvg) > threshold) {
    tap = true;
  }

  // Detect tap on Y-axis
  if (abs(Ydata[Ydata.size() - 1] - yAvg) > threshold) {
    tap = true;
  }

  // Detect tap on Z-axis
  if (abs(Zdata[Zdata.size() - 1] - zAvg) > threshold) {
    tap = true;
  }

  return tap;
}

bool Sensors::shakeDetected() {
  double X = 0;
  double Y = 0;
  double Z = 0;
  size_t minimumReadings = 10;
  
  // average the accel data of 10 instances
  for(int i = 0; i < min(minimumReadings, Xdata.size()); i++){
    X += Xdata[Xdata.size()-1-i];
    Y += Ydata[Ydata.size()-1-i];
    Z += Zdata[Zdata.size()-1-i];
  }
  X = X / min(minimumReadings, Xdata.size());
  Y = Y / min(minimumReadings, Xdata.size());
  Z = Z / min(minimumReadings, Xdata.size());
  double totalAccel = sqrt(X*X + Y*Y + Z*Z);
 
  //  Roll threshold value? Needs to be tested 
  int ROLL_THRESHOLD = 30;

  if (totalAccel > ROLL_THRESHOLD) { return true; }
  else { return false; }
}
// source: https://learn.adafruit.com/circuit-playground-d6-dice/shake-detect


State Sensors::getState() {
  return state;
}
