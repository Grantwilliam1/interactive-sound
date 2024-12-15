//33 IoT

# include <ArduinoBLE.h>

// BLECharacteristic humidityChar;
BLECharacteristic lightChar;
BLECharacteristic soundChar;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);

  Serial.println("BLE Central ready. Starting scan...");
  BLE.begin();
  BLE.scanForUuid("19b1054D-e8f2-537e-4f6c-d104768a1214");
  Serial.println("1");

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("2");
  BLEDevice peripheral = BLE.available();
  Serial.println(BLE.available());

  if(peripheral){
    if (peripheral.localName() != "maxpatSensor"){
      return;
    }
    Serial.println("3");
    BLE.stopScan();
    controlPer(peripheral);
    BLE.scanForUuid("19b1054D-e8f2-537e-4f6c-d104768a1214");
  }

}

void controlPer(BLEDevice peripheral){
  if (!peripheral.connect()) {
    Serial.println("Failed to connect!");
    return;
  }
  if (!peripheral.discoverAttributes()) {
    Serial.println("Attribute discovery failed!");
    peripheral.disconnect();
    return;
  }
  while (peripheral.connected()){
    // humidityChar = peripheral.characteristic("19b1054D-e8f2-537e-4f6c-d104768a1214");
    lightChar = peripheral.characteristic("19b1054D-e8f2-537e-4f6c-d104768a1215");
    soundChar = peripheral.characteristic("19b1054D-e8f2-537e-4f6c-d104768a1216");

    if (lightChar && soundChar){
      if (lightChar.canRead() && soundChar.canRead()) {
        int light, sound;
        lightChar.readValue((uint8_t*)&light, sizeof(light));
        soundChar.readValue((uint8_t*)&sound, sizeof(sound));

        Serial.print(light);
        Serial.print(" ");
        Serial.println(sound);
      }
    }
  }
}