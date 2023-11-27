#include <Arduino.h>
#include "NeuralNetwork.h"

// put function declarations here:
int myFunction(int, int);
NeuralNetwork *nn;
const int stack = 60;
float window[stack];
void setup() {
  // put your setup code here, to run once:
  nn = new NeuralNetwork();
}

void loop() {
  // put your main code here, to run repeatedly:
  #if DEBUG
  unsigned long start_us = micros();
  #endif
  //generate random test data & copy val to input buffer
  for (int i=0;i<stack;i++)
  {
    nn->getInputBuffer()[i] = (float)rand()/RAND_MAX;
  }
  // run inference
  float output = nn->predict();
  Serial.println(output);
  #if DEBUG
  Serial.print("Time for inference: ")
  Serial.println(micros()-start_us);
  #endif
  delay(1000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}