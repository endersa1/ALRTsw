/*

#include "C:/ALRT/ALRT/button.h/button.h.ino"
#include "C:/ALRT/ALRT/button/button.ino"
//#include "C:/ALRT/ALRT/shocker.h/shocker.h.ino"
//#include "C:/ALRT/ALRT/shocker/shocker.ino"
//#include "C:/ALRT/ALRT/sensors.h/sensors.h.ino"
//#include "C:/ALRT/ALRT/sensors/sensors.ino"
#include "C:/ALRT/ALRT/enums.h/enums.h.ino"

const int butPin = 21;
const int LED1_PIN = 1;
const int LED2_PIN = 4;
const int LED3_PIN = 6;
const int LED4_PIN = 5;
const int cshockPin = 7;
const int dshockPin = 2;
const int vibPin = 20;
const int batPin = 0;
//const int IMUPin =
//const int HRVPin =

//setup button, shocker, sensors
Button button = Button(butPin);
//Shocker shocker = Shocker(cshockPin, dshockPin);
//Sensors sensors = Sensors(IMUPin, HRVPin);
  
void setup() {

  //setup LEDs, vibrator, battery
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  pinMode(vibPin, OUTPUT);
  pinMode(batPin, INPUT);
  
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

void setVibrator(int on) {
  if (on) {
    digitalWrite(vibPin, HIGH);
  } else {
    digitalWrite(vibPin, LOW);
  }
}

int getCharge() {
  int charge = digitalRead(batPin);
  // convert to 1 through 4
  return charge;
}
  

void loop() {


  ///////////// test button //////////////////

  button.readButton();
  
  //button interrupt, skipping ON function
  if(button.getState() == HOLD) {
    setLEDs(1);
    setVibrator(0);
  } else if(button.getState() == ONE){
    setLEDs(2);
    setVibrator(0);
  } else if (button.getState() == RAPID) {
    setLEDs(3);
    setVibrator(1);
  } else if (button.getState() == REST) {
    setLEDs(4);
    setVibrator(0);
  } else {
    setLEDs(0);
    setVibrator(0);
  } 

  ///////////// end test button //////////////////
  
  
  }



  const int LED1_PIN = 1;

void setup() {
  Serial.begin(115200);
  pinMode(LED1_PIN, OUTPUT);
}

void loop() {
  Serial.println("hello");
  digitalWrite(LED1_PIN, HIGH);
  
  delay(1000);
  digitalWrite(LED1_PIN, LOW);
  delay(1000);
}  */



#include <Wire.h>
#include <MAX30105.h>

MAX30105 particleSensor;
const int ledPin = 1;  // Change this to the pin where your LED is connected

void setup() {
  // Initialize the MAX30102 sensor
  if (!particleSensor.begin()) {
    while (1); // Halt the program if the sensor is not found
  }

  // Set up the MAX30102 sensor with default settings
  particleSensor.setup();

  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Detect and calculate heart rate for 10 seconds
  unsigned long startTime = millis();
  unsigned long detectionDuration = 10000;  // 10 seconds
  unsigned long endTime = startTime + detectionDuration;

  float heartRate = 0.0;

  vector<uint32_t> vr

  while (millis() < endTime) {
    // Read the red and IR values from the sensor
    uint32_t redValue = particleSensor.getRed();
    uint32_t irValue = particleSensor.getIR();

    
    // Wait for a short duration before reading again
    delay(300);
  }

  heartRate = calculateHeartRate(redValue, irValue);

  // Display the calculated heart rate on the LED for the next 10 seconds
  unsigned long displayDuration = 10000;  // 10 seconds
  unsigned long displayEndTime = millis() + displayDuration;

  while (millis() < displayEndTime) {
    // Blink the LED at the same speed as the calculated heart rate
    if (heartRate > 0) {
      int blinkDuration = int(60000 / heartRate);  // Convert BPM to milliseconds
      digitalWrite(ledPin, HIGH);
      delay(blinkDuration / 2);  // LED on for half of the blink duration
      digitalWrite(ledPin, LOW);
      delay(blinkDuration / 2);  // LED off for the other half
    } else {
      // No heart rate detected, keep the LED off
      digitalWrite(ledPin, LOW);
    }
  }
}

float calculateHeartRate(uint32_t redValue, uint32_t irValue) {
  // Implement your heart rate calculation logic here
  // This is a simplified example; you may need more complex algorithms for accurate results
  // For simplicity, I'm just returning a constant value (90 BPM) in this example
  return 90.0;
}
