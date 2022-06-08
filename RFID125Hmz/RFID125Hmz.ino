#include "BluetoothSerial.h"
#include <SoftwareSerial.h>
SoftwareSerial RFID(3,1); // RX and TX
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial BT;

String text;
String CardNumber; 

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

void setup()
{
  Serial.begin(9600);
  RFID.begin(9600);
   BT.begin("Gannapp");
    Serial.println("El dispositivo Bluetooth está listo para emparejar");
    BT.register_callback(callback_function);
  Serial.println("Acerca tu tarjeta RFID...");
  CardNumber = "0006480377"; 
}
char c;

void loop()
{
  
  while (RFID.available() > 0) {
    delay(5);
    c = RFID.read();
    text += c;
  }
  if (text.length() > 20)
  check();
  text = "";
}

void check()
{
  text = text.substring(1, 11);
  Serial.println("Tarjeta ID : " + text);
  Serial.println("Acceso ID : " + CardNumber);
   BT.println("Tarjeta ID : " + text);
  

  if (CardNumber.indexOf(text) >= 0) {
    Serial.println("Acceso aceptado");
    BT.println("Nuevo registro");
  }
  else {
    Serial.println("Acceso denegado");
  }
  delay(2000);
  Serial.println(" ");
  Serial.println("Acerca tu tarjeta RFID …");
}
