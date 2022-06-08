const int verde = 12;
const int rojo =  14;
const int amarillo = 27;
#include <HTTPClient.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#include <SPI.h>
#include <MFRC522.h>
Servo myservo;
int dt = 100;
const char* ssid = "Arrayago Wifi";
const char* password =  "36110210";
#define RST_PIN  0    //Pin 0 para el reset del RC522
#define SS_PIN  5   //Pin 5 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); ///Creamos el objeto para el RC522
String User1 = "carabana Nª";
String User2 = "Carabana Nª";
String id1 = "Nª Color=";
String id2 = "Nª color=";
void setup() {
  myservo.attach(25);
  pinMode(verde, OUTPUT);
  pinMode(rojo,  OUTPUT);
  pinMode(amarillo, OUTPUT);
  Serial.begin(115200); 
  SPI.begin();        
  mfrc522.PCD_Init();
  Serial.println("Control de acceso:");
  WiFi.begin(ssid, password);
     Serial.print("Conectando...");
     while (WiFi.status() != WL_CONNECTED) { 
   
     Serial.print(".");
  }
   Serial.print("Conectado con éxito, mi IP es: ");
  Serial.println(WiFi.localIP());
}

byte ActualUID[4];
byte  Usuario1[4]= {0x33, 0x5E, 0xAC, 0x14};
byte  Usuario2[4]= {0xC7, 0x7E, 0x63, 0xC8};
void loop() {
 digitalWrite(verde, LOW);
digitalWrite(rojo, LOW);
digitalWrite(amarillo, HIGH);
  
  // Revisamos si hay nuevas tarjetas  presentes
  if ( mfrc522.PICC_IsNewCardPresent()) 
  {  
  if ( mfrc522.PICC_ReadCardSerial()) 
  {
 
   Serial.print(F("Card UID:"));
   for (byte i = 0; i < mfrc522.uid.size; i++) {
   Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
   Serial.print(mfrc522.uid.uidByte[i], HEX);   
   ActualUID[i]=mfrc522.uid.uidByte[i];          
   } 
   Serial.print(" ");                 
                    
  if(compareArray(ActualUID,Usuario1)){
     if(WiFi.status()== WL_CONNECTED){   
    HTTPClient http;
    http.begin ("**************************************?user=" + String(User1)+ "&trj=" + String(id1));
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
    int codigo_respuesta = http.GET();
      
    if(codigo_respuesta >0){
      Serial.println("Código HTTP ► " + String(codigo_respuesta));   
      if(codigo_respuesta == 200){
        String cuerpo_respuesta = http.getString();
        Serial.println("El servidor respondió ▼ ");
        Serial.println(cuerpo_respuesta);
        
      }
    }else{
     Serial.print("Error enviando GET, código: ");
     Serial.println(codigo_respuesta);
    }
    http.end();
    }else{
     Serial.println("Error en la conexión WIFI");
  }
  Serial.println("bIenvenida Gisella.");
  myservo.write(90);
  delay(100);                  
  digitalWrite(verde, HIGH);
  digitalWrite(amarillo, LOW);
  }
  else if(compareArray(ActualUID,Usuario2)){
    if(WiFi.status()== WL_CONNECTED){   
    HTTPClient http;
    http.begin("**************************************?user=" + String(User2)+ "&trj=" + String(id2));
     http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
    int codigo_respuesta = http.GET();  
    if(codigo_respuesta >0){
      Serial.println("Código HTTP ► " + String(codigo_respuesta));   
      if(codigo_respuesta == 200){
        String cuerpo_respuesta = http.getString();
        
        Serial.println("El servidor respondió ▼ ");
        Serial.println(cuerpo_respuesta);
        
      }
    }else{
     Serial.print("Error enviando GET, código: ");
     Serial.println(codigo_respuesta);
     
    }
    http.end();
    }else{
     Serial.println("Error en la conexión WIFI");
  }
  Serial.println("Bienvenido Martin...");
  myservo.write(90);
  delay(100);
  digitalWrite(verde, HIGH);
  digitalWrite(amarillo, LOW);
  }
  else{
  Serial.println("Acceso denegado...");
  digitalWrite(rojo, HIGH);
  digitalWrite(amarillo, LOW);
  }
  delay (3000);
  // Terminamos la lectura de la tarjeta tarjeta  actual
  mfrc522.PICC_HaltA();
  }          
  } 
  
  myservo.write(0);
}

//Función para comparar dos vectores
 boolean compareArray(byte array1[],byte array2[])
{
  if(array1[0] != array2[0])return(false);
  if(array1[1] != array2[1])return(false);
  if(array1[2] != array2[2])return(false);
  if(array1[3] != array2[3])return(false);
  return(true);
}
