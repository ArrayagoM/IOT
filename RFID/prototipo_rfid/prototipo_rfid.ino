const int verde = 3;
const int rojo =  4;
const int amarillo = 5;
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522 ( SS_PIN, RST_PIN ) ;    // Cree la instancia de MFRC522.

 byte LecturaUID[4];
byte Usuario1[4]= {0xD1, 0x4E, 0x23, 0x21};
byte Usuario2[4]= {0x0C, 0x8A, 0x2A, 0x4A};
//configuración vacía () 
void setup() {
  Serial.begin ( 9600 ) ;    // Iniciar una comunicación en serie
  SPI.begin () ;       // Iniciar bus SPI
  mfrc522.PCD_Init () ;    // Iniciar MFRC522
  Serial.println ( "Aproxima su tarjeta al lector ..." ) ;
  Serial.println ("ya esta todo listo.") ;
    pinMode(verde, OUTPUT);
  pinMode(rojo,  OUTPUT);
  pinMode(amarillo, OUTPUT);
}
//bucle vacío () 
void loop() {
  digitalWrite(verde, LOW);
   digitalWrite(rojo, LOW);
   digitalWrite(amarillo, HIGH);
  // Look para nuevas tarjetas
  if  ( ! mfrc522.PICC_IsNewCardPresent ());
 
  {
     return;
  }
  // Selecciona una de las cartas
  if  ( ! mfrc522.PICC_ReadCardSerial ()); 
  {
    return;
  }
 Serial.print("UID:");
for (byte i = 0; i < mfrc522.uid.size; i++) {
  if (mfrc522.uid.uidByte[i] < 0x10){
    Serial.print(" 0");
  }
  Serial.println () ;
  Serial.print ( "Hola marica:" ) ;
  //const.toUpperCase () ;
//  if  ( content.substring ( 1 )  ==  "D1 4E 23 21" ) // cambia aquí el UID de la tarjeta / tarjetas a las que quieres dar acceso
  {
    Serial.println ( "Acceso autorizado" ) ;
    Serial.println () ;
    digitalWrite(verde, HIGH);
         digitalWrite(rojo, LOW);
         digitalWrite(amarillo, LOW);
    delay ( 3000 ) ;
  }
  else if (comparaUID(LecturaUID, Usuario2)){
    Serial.println("Bienvenido Usuario 2");
         digitalWrite(verde, HIGH);
         digitalWrite(rojo, LOW);
         digitalWrite(amarillo, LOW);
         delay (2000);
  }
 
 else    {
    Serial.println ( "Acceso denegado" ) ;
    digitalWrite(verde, LOW);
         digitalWrite(rojo, HIGH);
         digitalWrite(amarillo, LOW);
    delay ( 3000 ) ;
  }
} 
