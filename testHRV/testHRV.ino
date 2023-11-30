#include <Wire.h>
#include <MAX30105.h>

MAX30105 particleSensor;

void setup() {
  Serial.begin(115200);

  // Initialize the MAX30102 sensor
  if (!particleSensor.begin()) {
    Serial.println("MAX30102 was not found. Please check your wiring!");
    while (1);
  }

  // Set up the MAX30102 sensor with default settings
  particleSensor.setup();
}

void loop() {
  // Read the red and IR values from the sensor
  uint32_t redValue = particleSensor.getRed();
  uint32_t irValue = particleSensor.getIR();

  // Print the values to the serial monitor
  Serial.print("Red: ");
  Serial.print(redValue);
  Serial.print("\tIR: ");
  Serial.println(irValue);

  // Wait for a short duration before reading again
  delay(1000);
}
