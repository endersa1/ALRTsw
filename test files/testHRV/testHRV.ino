

#include <Wire.h>
#include <MAX30105.h>
#include <MPU6050.h>

MPU6050 mpu;

#include "heartRate.h"

MAX30105 particleSensor;

const int LED1_PIN = 1;
const int LED2_PIN = 4;
const int LED3_PIN = 6;
const int LED4_PIN = 5;

 int num = 0;
 uint32_t lastchange = millis();

void setup() {

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  Serial.begin(115200);

  // Initialize the MAX30102 sensor
  if (!particleSensor.begin()) {
    Serial.println("MAX30102 was not found. Please check your wiring!");
    while (1);
  }

  // Set up the MAX30102 sensor with default settings
  particleSensor.setup();

  Wire.begin();
  mpu.initialize();
  // Verify connection
  if (mpu.testConnection()) {
    Serial.println("MPU-6050 connection successful");
  } else {
    Serial.println("MPU-6050 connection failed");
    while (1);
  }

  
}

void setLEDs(int num) {
  switch(num) {
    case 0:
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);
      digitalWrite(LED3_PIN, LOW);
      digitalWrite(LED4_PIN, LOW);
      break;
    case 1:
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, LOW);
      digitalWrite(LED3_PIN, LOW);
      digitalWrite(LED4_PIN, LOW);
      break;
    case 2:
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, HIGH);
      digitalWrite(LED3_PIN, LOW);
      digitalWrite(LED4_PIN, LOW);
   break;
    case 3:
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, HIGH);
      digitalWrite(LED3_PIN, HIGH);
      digitalWrite(LED4_PIN, LOW);
      break;
    case 4:
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, HIGH);
      digitalWrite(LED3_PIN, HIGH);
      digitalWrite(LED4_PIN, HIGH);
      break;
  }
 
}


void loop() {
  // Read the red and IR values from the sensor
  //int32_t redValue = particleSensor.getRed();
  int32_t irValue = particleSensor.getIR();

  setLEDs(4);

  //Serial.println(redValue);
  //Serial.println(irValue);

  bool beat = checkForBeat(irValue);

  //Serial.println(beat);

  if(beat) {
    num++;
    
  }



if (millis() - lastchange > 29500 && millis() - lastchange < 30500) {
    int bpm = num;
    num = 0;
    Serial.println(bpm);
    lastchange = millis();
}

// Read accelerometer data
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  // Print X, Y, and Z values
  Serial.print("X-axis: ");
  Serial.print(ax);
  Serial.print("\tY-axis: ");
  Serial.print(ay);
  Serial.print("\tZ-axis: ");
  Serial.println(az);
  

  /*

  if(millis()%100 == 0) {
    int bpm = num;
    num = 0;
    Serial.print("millis ");
    Serial.println(millis());
    Serial.println(bpm);
  }
  */


  // Wait for a short duration before reading again
  delay(400);
}





/*
void setup() {
  Serial.begin(9600);
  pinMode(1, OUTPUT);
}

void loop() {

  digitalWrite(1, HIGH);

  Serial.println("HI");

  delay(2000);

  digitalWrite(1, LOW);

  delay(2000);

  
  
}

*/
