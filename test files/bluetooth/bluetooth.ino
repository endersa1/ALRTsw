#include <BLEDevice.h>

BLEServer *pServer;
BLECharacteristic *pCharacteristic;

void setup() {
  Serial.begin(115200);
  BLEDevice::init("BeetleESP32C3");
  
  pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(BLEUUID("0000180D-0000-1000-8000-00805F9B34FB"));
  
  pCharacteristic = pService->createCharacteristic(
                      BLEUUID("00002A37-0000-1000-8000-00805F9B34FB"),
                      BLECharacteristic::PROPERTY_READ
                    );

  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(pService->getUUID());
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Beetle ESP32C3 is now discoverable!");
}

void loop() {
  // Your code here
}
