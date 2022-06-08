#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

LiquidCrystal_I2C lcd(0x3F,16,2);

extern int motor = 18;
int SensorPin = 0;

WiFiClient wificlient;
const char* ssid = "***********";
const char* pass ="***********";
const char* Nombre= "*****";
  
void setup() {
  pinMode(2, OUTPUT);
  
  Serial.begin(115200);
  
  pinMode(motor, OUTPUT);

lcd.init();
lcd.backlight();
  
  WiFi.begin(ssid,pass);
  Serial.print("Conectando...");
  while (WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
Serial.print("Conectado con éxito, mi IP es: ");
  Serial.println(WiFi.localIP());
  
}

void loop() {
  
  int h = analogRead(SensorPin);
   lcd.setCursor(0,0);
  Serial.print("La humedad del suelo es: ");
  lcd.print("La humedad del suelo es: ");
  lcd.print(h);
  Serial.println(h);
  
  if(h >=460){
    digitalWrite(2, LOW);
    digitalWrite(motor, HIGH);
    delay(15000);
    
  }
else {
  digitalWrite(2,HIGH);
}
if(WiFi.status()== WL_CONNECTED){  
  
    HTTPClient http;
   
    http.begin("https://****************************" + String(h) + "&nombre=" + String(Nombre)); 
          
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
    int codigo_respuesta = http.GET();   
    
    if(codigo_respuesta>0){
      Serial.println("Código HTTP ► " + String(codigo_respuesta));
      if(codigo_respuesta == 200){
        String cuerpo_respuesta = http.getString();
        Serial.println("El servidor respondió ▼ ");
        Serial.println(cuerpo_respuesta);
        lcd.setCursor(10,0);
        lcd.print(cuerpo_respuesta);

}

}else{
    
     Serial.print("Error enviando GET, código: ");
     Serial.println(codigo_respuesta);
     

    }
        http.end(); 

  }else{

     Serial.println("Error en la conexión WIFI");
     lcd.print("Error en la conexión WIFI");

  }

   delay(20000);
}
