#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(115200);

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

void loop() {
  // Read accelerometer data
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  // Print X, Y, and Z values
  Serial.print("X-axis: ");
  Serial.print(ax);
  Serial.print("\tY-axis: ");
  Serial.print(ay);
  Serial.print("\tZ-axis: ");
  Serial.print(az);

  // Calculate magnitude
  float magnitude = sqrt(ax * ax + ay * ay + az * az);

  // Print magnitude to Serial Monitor
  Serial.print("\tMagnitude: ");
  Serial.println(magnitude);

  // Wait for 1 second
  delay(1000);
}
