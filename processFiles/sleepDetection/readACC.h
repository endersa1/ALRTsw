#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

struct accelData {
  double X;
  double Y;
  double Z;
};
/* Get a new sensor event */
sensors_event_t event;

accelData dat;

/*Thinking about using a class to handle (recent) memory of accM's movement
class accHandlr
{
public:
	const int maxMemory;
	accelData pos[maxMemory];

}*/
