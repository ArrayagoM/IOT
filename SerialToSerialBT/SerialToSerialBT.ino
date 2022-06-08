//Este código de ejemplo está en el dominio público (o con licencia CC0, a su elección).
//Por Evandro Copercini - 2018
//
//Este ejemplo crea un puente entre Serial y Classical Bluetooth (SPP)
//y también demostrar que SerialBT tiene las mismas funcionalidades de un Serial normal

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
const int led = 2;
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth nombre del dispositivo
  Serial.println("El dispositivo comenzó, ahora puedes emparejarlo con bluetooth!");

  pinMode(led, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
    if (SerialBT == 49){
      digitalWrite(led, HIGH);
    }
    if (SerialBT == 48){
      digitalWrite(led, LOW);
    }
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  
  delay(20);
}
