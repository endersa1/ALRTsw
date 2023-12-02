#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

#define DEBUG 1
Adafruit_MMA8451 mma = Adafruit_MMA8451();

struct accelData {
  double X;
  double Y; 
  double Z;
};

void setup(void) {
  Serial.begin(9600);
  #if DEBUG
  Serial.println("Adafruit MMA8451 test!");
  #endif
  accelData dat;
  #if DEBUG
  
  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  #endif
  mma.setRange(MMA8451_RANGE_2_G);
  #if DEBUG
  Serial.print("Range = "); Serial.print(2 << mma.getRange());  
  Serial.println("G");
  #endif
}

void loop() {
  // Read the 'raw' data in 14-bit counts
  mma.read();

  /* Get a new sensor event */ 
  sensors_event_t event; 
  mma.getEvent(&event);
  
  #if DEBUG
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: \t"); Serial.print(event.acceleration.x); Serial.print("\t");
  Serial.print("Y: \t"); Serial.print(event.acceleration.y); Serial.print("\t");
  Serial.print("Z: \t"); Serial.print(event.acceleration.z); Serial.print("\t");
  Serial.println("m/s^2 ");
  #endif
  dat.X = event.acceleration.x;
  dat.Y = event.acceleration.y;
  dat.Z = event.acceleration.z;

  delay(1000);
  
  // how to return dat? - change to cpp

}
