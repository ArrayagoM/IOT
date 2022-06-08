const int verde = 12;
const int rojo =  14;
const int amarillo = 27;

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         0         
#define SS_PIN          5   
MFRC522::MIFARE_Key Key; 
    
MFRC522 mfrc522(SS_PIN, RST_PIN);  

byte LecturaUID[4];
byte Usuario1[4]= {0X209, 0X78, 0X35, 0X33};
byte Usuario2[4]= {0x0C, 0x8A, 0x2A, 0x4A};

void setup() {
  Serial.begin(115200);   
  SPI.begin();        
  mfrc522.PCD_Init();
  Serial.println("listo");

  pinMode(verde, OUTPUT);
  pinMode(rojo,  OUTPUT);
  pinMode(amarillo, OUTPUT);
}

void loop() {
   digitalWrite(verde, LOW);
   digitalWrite(rojo, LOW);
   digitalWrite(amarillo, HIGH);

  if ( ! mfrc522.PICC_IsNewCardPresent()) 
    return;

  if ( ! mfrc522.PICC_ReadCardSerial())
    return;
   
Serial.print("UID:");
for (byte i = 0; i < mfrc522.uid.size; i++) {
  if (mfrc522.uid.uidByte[i] < 0x10){
    Serial.print(" 0");
  }
  else{
  Serial.print(" ");
}
Serial.print(mfrc522.uid.uidByte[i], HEX);
LecturaUID[i]=mfrc522.uid.uidByte[i];
}

  Serial.print("/t");
 if(comparaUID(LecturaUID, Usuario1)){
  Serial.println("Bienvenido Usuario 1");
         digitalWrite(verde, HIGH);
         digitalWrite(rojo, LOW);
         digitalWrite(amarillo, LOW);
         delay (2000);
  }   
else if (comparaUID(LecturaUID, Usuario2)){
    Serial.println("Bienvenido Usuario 2");
         digitalWrite(verde, HIGH);
         digitalWrite(rojo, LOW);
         digitalWrite(amarillo, LOW);
         delay (2000);
  }
  else {
    Serial.println("accesodenegado");
         digitalWrite(verde, LOW);
         digitalWrite(rojo, HIGH);
         digitalWrite(amarillo, LOW);
         delay (2000);
   
  }  
 mfrc522.PICC_HaltA();
 
}

boolean comparaUID(byte lectura[],byte usuario[])
{
  for (byte i=0; i > mfrc522.uid.size; i++){
  return (false);
  }
  
  return(true);
}
