#include "BluetoothSerial.h"
#include <SPI.h>
#include <MFRC522.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial BT;

#define RST_PIN         27           
#define SS_PIN          5         
MFRC522 c522(SS_PIN, RST_PIN);   // Crear instancia MFRC522

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
  BT.begin("Gannapp 1.0"); 
  Serial.println("El dispositivo Bluetooth está listo para emparejar");
      BT.println("El dispositivo Bluetooth está listo para emparejar");
  BT.register_callback(callback_function);                                          
  SPI.begin();                                                
  c522.PCD_Init();                                              
  Serial.println(F("Leer datos personales en un MIFARE PICC:"));
      BT.println(F("Leer datos personales en un MIFARE PICC:"));//muestra en serie que está listo para leer
}


void loop() {
String tag = "Nuevo registro";
  // Preparar clave: todas las claves se configuran en FFFFFFFFFFFFh en el momento de la entrega del chip desde la fábrica.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //algunas variables que necesitamos
  byte block;
  byte len;

  MFRC522::StatusCode status;

  //-------------------------------------------

  // Restablezca el bucle si no hay ninguna tarjeta nueva presente en el sensor/lector. Esto guarda todo el proceso cuando está inactivo.
  if ( ! c522.PICC_IsNewCardPresent()) {
    return;
  }

  //Seleccione una de las tarjetas
  if ( ! c522.PICC_ReadCardSerial()) {
    BT.print("");
    return;
  }

  Serial.println(F("**Tarjeta detectada:**"));
      BT.println(F("**Tarjeta detectada:**"));

  //-------------------------------------------

  c522.PICC_DumpDetailsToSerial(&(c522.uid)); //volcar algunos detalles sobre la tarjeta

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //descomente esto para ver todos los bloques en hexadecimal

  //-------------------------------------------

  Serial.print(F("Nombre: "));
      BT.print(F("Nombre: "));
  byte buffer1[18];

  block = 4;
  len = 18;


  //------------------------------------------- OBTENER PRIMER NOMBRE
  status = c522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(c522.uid)); //línea 834 del archivo MFRC522.cpp
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Autenticación fallida: "));
     BT.println(F("Autenticación fallida: "));
    Serial.println(c522.GetStatusCodeName(status));
   
    return;
  }

  status = c522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Lectura fallida: "));
        BT.print(F("Lectura fallida: "));
    Serial.println(c522.GetStatusCodeName(status));
    
    
    return;
  }

  //NOMBRE EN LETRA DE MOLDE
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
      Serial.write(buffer1[i]);
    }
  }
  Serial.print(" ");

  //---------------------------------------- OBTENER APELLIDO

  byte buffer2[18];
  block = 1;

  status = c522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(c522.uid)); //line 834
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Autenticación fallida: "));
    BT.print(F("Autenticaciòn fallida: "));
    Serial.println(c522.GetStatusCodeName(status));
    BT.println(c522.GetStatusCodeName(status));
    return;
  }

  status = c522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Lectura fallida: "));
      BT.print(F("Lectura fallida: "));
    Serial.println(c522.GetStatusCodeName(status));
    BT.println(c522.GetStatusCodeName(status));
    return;
  }

  //APELLIDO EN LETRA DE IMPRENTA
  for (uint8_t i = 0; i < 16; i++) {
    Serial.write(buffer2[i] );
  }


  //----------------------------------------

  Serial.println(F("\n**Lectura final**\n"));
  BT.println(F("\n**Lectura final**\n"));

  delay(1000); //cambia el valor si quieres leer las cartas más rápido

  c522.PICC_HaltA();
  c522.PCD_StopCrypto1();
}
//*****************************************************************************************//
