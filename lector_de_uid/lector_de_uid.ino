#include "BluetoothSerial.h"
#include <SPI.h>
#include <MFRC522.h>
const int RST_PIN = 27;
const int SS_PIN = 5;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial BT;


MFRC522 mfrc522(SS_PIN, RST_PIN);
void printArray(byte *buffer, byte bufferSize){
  for (byte i = 0; i < bufferSize; i++){
    Serial.print(buffer[i] < 0x10 ? " 0 " : " ");
    Serial.print(buffer[i] , HEX);
    BT.print(buffer[i], HEX);
  }
}
void callback_function(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_START_EVT) {
    Serial.println("Inicializado SPP");
  }
  else if (event == ESP_SPP_SRV_OPEN_EVT ) {
    Serial.println("Cliente conectado");
  }
  else if (event == ESP_SPP_CLOSE_EVT  ) {
    Serial.println("Cliente desconectado");
  }

}
void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
 BT.begin("Gannapp"); 
  Serial.println("El dispositivo Bluetooth está listo para emparejar");
  BT.register_callback(callback_function);
}

void loop() {
  String tag = "Nuevo registro";
  if (mfrc522.PICC_IsNewCardPresent())
  {
    if (mfrc522.PICC_ReadCardSerial()) {
      Serial.print(tag);
      BT.println(tag);
      printArray(mfrc522.uid.uidByte, mfrc522.uid.size);

      mfrc522.PICC_HaltA();
    }
  }
delay(25);
}
