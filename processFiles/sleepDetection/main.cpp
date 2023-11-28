#include <Arduino.h>
#include "NeuralNetwork.h"
#include <vector>
//#include "sensor.h" (<- should remove .ino) will put where accelerometer data ( recorded magnitude ) is implemeneted with /**/
// put function declarations here:
int myFunction(int, int);
NeuralNetwork *nn;
const int stack = 60;
int count = 0;
std::vector<double> window;
float temp[stack];
void normByTwos(int n, double win[], float norm[])
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
    if(i%2==1) norm[i] = (float)(win[i]-mnHR)/(dHR);
    else norm[i] = (float)(win[i]-mnACC)/(dACC);
  }
}
float magnitude(float x, float y, float z)
{
  return sqrt(x*x + y*y + z*z);
}
void setup() {
  // put your setup code here, to run once:
  nn = new NeuralNetwork();
  //window.resize(stack);
}
//std::max_element()

void loop() {
  // put your main code here, to run repeatedly:
  /*
  int len = Xdata.size()

  window.push_back(magnitide(Xdata[len],Ydata[len],Zdata[len]));
  window.push_back(hr);//last hr reading
  if (window.size() > stack) window.erase(stack); // deletes last element (if 61 long, erase index 60 [61st item])
  */

  #if DEBUG
  unsigned long start_us = micros();
  #endif
  //generate random test data & copy val to input buffer
  for (int i=0;i<stack;i++)
  {
    nn->getInputBuffer()[i] = (float)rand()/RAND_MAX;
  }
  /*
  //normalize input data
  normByTwos(window.size(), window, temp);
  for (int i =0; i<window.size(); i++)
  {
    
    nn->getInputBuffer()[i] = temp[i];
  }*/
  // run inference
  float output = nn->predict();
  if (window.size()!=stack) return;
  Serial.println(output);
  #if DEBUG
  Serial.print("Time for inference (us): ")
  Serial.println(micros()-start_us);
  #endif
  delay(1000);//have to do multi thread esc implementation, so watch deosn't halt in between readings
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}