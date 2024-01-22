#include "button.h"
#include "shocker.h"
#include "sensors.h"
#include "enums.h"

//Bluetooth includes
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <base64.h>
#define SERVICE_UUID           "18ac0ea4-897d-11ee-b9d1-0242ac120002" // UART service UUID
#define CHARACTERISTIC_UUID_RX "18ac11c4-897d-11ee-b9d1-0242ac120002"
#define CHARACTERISTIC_UUID_TX "18ac1318-897d-11ee-b9d1-0242ac120002"
BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
bool deviceConnected = false;
uint8_t txValue = 0;

//Bluetooth initial settings variable values and dummy test variables
std::string incomingValue = "Be";//Test
int timeBetweenShocks = 2; //Default 2, can go up to 10
int restTimeBetweenShockIdle = 2; //Default 2, can go up to 10
int shockLevel = 1; //Default 1, can go up to 5
int configStatus = 0; //When configured = 1

//Bluetooth: Initialize settingsArray to hold default values of user settings
const int settingsArraySize = 4;
int settingsArray[settingsArraySize];


//Bluetooth Callbacks
//Bluetooth connect/disconnect processing. Triggered automatically when a connect/disconnect event occurs
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {   //This function will be executed when Bluetooth is connected
      Serial.println("Bluetooth connected");
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {  //This function will be executed when Bluetooth is disconnected
      Serial.println("Bluetooth disconnected");
      deviceConnected = false;
      delay(500); // give the bluetooth stack the chance to get things ready
      pServer->startAdvertising(); // restart advertising

    }
};

/****************Data receiving section*************/
//Bluetooth receive data processing. Triggered automatically when data is received
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();//Receive data and assign it to rxValue
      unsigned char string[15];
      incomingValue = rxValue;

      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++){
          Serial.print(rxValue[i]);
        }
        Serial.println();
        Serial.println("*********");
        if (strncmp(rxValue.c_str(), "BSC", 3) == 0) {
          // Extract the numeric part and convert it to an integer
          timeBetweenShocks = atoi(rxValue.substr(3).c_str());
          settingsArray[0] = timeBetweenShocks;
        }
        else if (strncmp(rxValue.c_str(), "SIC", 3) == 0) {
          // Extract the numeric part and convert it to an integer
          restTimeBetweenShockIdle = atoi(rxValue.substr(3).c_str());
          settingsArray[1] = restTimeBetweenShockIdle;
          sensors.updateRestTime(restTimeBetweenShockIdle);
          Serial.println("Rest time between shcok and idle has changed: ", restTimeBetweenShockIdle);
        }
         else if (strncmp(rxValue.c_str(), "SLC", 3) == 0) {
          // Extract the numeric part and convert it to an integer
          shockLevel = atoi(rxValue.substr(3).c_str());
          settingsArray[2] = shockLevel;
        }
        else if (strncmp(rxValue.c_str(), "CFG", 3) == 0) {
          // Extract the numeric part and convert it to an integer
          configStatus = atoi(rxValue.substr(3).c_str());
          settingsArray[3] = configStatus;
        }

        
      }
    }
};
/***************************************/

void BLEBegin(){
  // Create the BLE Device
  BLEDevice::init("EASYBLUE");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  // pServer->setMTU(512); // Experiment with a larger MTU size

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pTxCharacteristic = pService->createCharacteristic(
                    CHARACTERISTIC_UUID_TX,
                    BLECharacteristic::PROPERTY_NOTIFY
                  );

  pTxCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_RX,
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
}
//End Bluetooth callbacks

const int butPin = 21;
const int LED1_PIN = 1;
const int LED2_PIN = 4;
const int LED3_PIN = 6;
const int LED4_PIN = 5;
const int cshockPin = 7;
const int dshockPin = 2;
const int vibPin = 20;
const int batPin = 0;
//const int SDAPin = 8;
//const int SCLPin = 9;
unsigned long lastLEDChangeTime = millis();

//setup button, shocker, sensors
Button button = Button(butPin);
//Shocker shocker = Shocker(cshockPin, dshockPin);
Sensors sensors = Sensors();


void setupBluetooth() {
  Serial.begin(115200);
  BLEBegin();  //Initialize Bluetooth

  //Potentially try to save previous defaults on EEPROM or database and read from there
  settingsArray[0] = 2;
  settingsArray[1] = 2;
  settingsArray[2] = 1;
  settingsArray[3] = 0;
}
  
void setup() {
  
  //setup LEDs, vibrator, battery
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  pinMode(vibPin, OUTPUT);
  pinMode(batPin, INPUT);

  Serial.begin(115200);

  setupBluetooth();
  
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

int getCharge() { //needs testing
  int charge = digitalRead(batPin);
  // convert to 1 through 4
  return charge;
}

void loop() {

  ////////////// BLUETOOTH /////////////////////


  //int newRestTime = 0;
  //sensors.updateRestTime(newRestTime);
  if (deviceConnected) {  //If there is a Bluetooth connection, send data
    if(incomingValue == "Be"){
      pTxCharacteristic->setValue("This is cool");  //Send string
      pTxCharacteristic->notify();
      delay(10000); // bluetooth stack will go into congestion, if too many packets are sent
      pTxCharacteristic->setValue("DFRobot");  //Send string
      pTxCharacteristic->notify();
      delay(10000); // bluetooth stack will go into congestion, if too many packets are sent
    }
    else{
      pTxCharacteristic->setValue(incomingValue);  //Send string
      pTxCharacteristic->notify();
      delay(10000);
    }
  }

 //////////////////////////////////////////////
  
  //read button input
  button.readButton();

  //turn off LEDs after 5 seconds
  if(lastLEDChangeTime - millis() > 5000) {
    setLEDs(0);
  }
  
  //button interrupt, skipping ON function
  if(button.getState() == RAPID) {
    
    //kill switch
    //turn off shocker and vibrator, delay (turn off?)
    //shocker.set(0);
    Serial.println("shock off");
    setVibrator(1);
    delay(30000); //delays 30 seconds - for debugging only
    
  } else if(button.getState() == HOLD) {
    
     //turn on shocker
     //shocker.set(1);
     Serial.println("shock on");
     setVibrator(0);
     
  } else {

  //continue reading input and process
  int charge = getCharge();
  sensors.setState();
  
  //output
  //vibrator and shocker
  switch(sensors.getState()) {
        case IDLE:
            //set vibrator and shocker to 0
            setVibrator(0);
            //shocker.set(0);
            Serial.println("shock off");
            break;
        case VIBRATE:
            //set shocker to 0 and implement vibrating
            setVibrator(1);
            //shocker.set(0);
            Serial.println("shock off");
            break;
        case SHOCK:
            //set vibrator to 0 and implement shocking
            setVibrator(0);
            //shocker.set(1);
            Serial.println("shock on");
            break;
    }

    //LEDS
    if(sensors.isTapped()) { //condition for lights to be shown
      setLEDs(charge);
      lastLEDChangeTime = millis();
    }
    
  }
}
