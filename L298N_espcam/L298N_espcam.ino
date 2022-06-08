#include<WiFi.h>

const char* ssid = "Arrayago Wifi";
const char* password ="#Martin36110210";

WiFiServer server(80);

String header;
String output12State = "off";
String output13State = "off";
String output15State = "off";
String output14State ="off";

const int delante = 12;
const int atras = 13;
const int izquierda = 15;
const int derecha = 14;

unsigned long currentTime = millis();

unsigned long previousTime = 0;

 const long previousTime = 2000;
 
void setup() {
  Serial.begin(115200);

  pinMode( delante, OUTPUT);
  pinMode(atras, OUTPUT);
  pinMode(izquierda, OUTPUT);
  pinMode(derecha,OUTPUT);

  digitalWrite(delante, LOW);
  digitalWrite(atras, LOW);
  digitalWrite(izquierda, LOW);
  digitalWrite(derecha, LOW);

  Serial.print("conectando wi-fi");
  Serial.println(ssid);
  Serial.println(ssid, password);
  while (WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
Serial.print("");
Serial.print("conectado con exito");
Serial.println("Numero de IP:");
Serial.print(WiFi.localIP());
sever.begin();
}

void loop() {
   WiFiClient client = server.available();

   if (client) {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("Martin estas conectado...");
    String currentLine = "";
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
    currentTime = millis();
    if(client.available()){
      char c = client.read();
      Serial.write(c);
      header += c;
      if ( c== '\n'){
        if (currentLine.length() == 0) {
          client.println("HTTP/1.1 200 OK");
          client.println("Tipo de contenido:texto/html");
          client.print("Conexion: cerrada");
          client.println();
          
          if (header.indexOf("GET /12/on") >=0){
            Serial.println("GPIO 12 on");
            output12State = "on";
            digitalWrite(delalnte, HIGH);
            digitalWrite(atras, LOW);
          } else if (header.indexOf("GET/12/off") >=0){
            Serial.println("GPIO 12 off");
            output12State = "off";
            digitalWrite(delante, LOW);
            digitalWrite(atras, LOW);
          }else if (header.indexOf("GET /13/on") >=0){
            Serial.println("GPIO 13 on");
            output13State = "on";
            digitalWrite(delalnte, LOW);
            digitalWrite(atras, HIGH);
          } else if (header.indexOf("GET/13/off") >=0){
            Serial.println("GPIO 13 off");
            output13State = "off";
            digitalWrite(delante, LOW);
            digitalWrite(atras, LOW);    
        }
        else if (header.indexOf("GET /15/on") >=0){
            Serial.println("GPIO 15 on");
            output15State = "on";
            digitalWrite(izquierda, HIGH);
            digitalWrite(derecha, LOW);
          } else if (header.indexOf("GET/15/off") >=0){
            Serial.println("GPIO 15 off");
            output15State = "off";
            digitalWrite(izquierda, LOW);
            digitalWrite(derecha, LOW); 
      }else if (header.indexOf("GET /14/on") >=0){
            Serial.println("GPIO 14 on");
            output14State = "on";
            digitalWrite(izquierda, LOW);
            digitalWrite(derecha, HIGH);
          } else if (header.indexOf("GET/14/off") >=0){
            Serial.println("GPIO 14 off");
            output14State = "off";
            digitalWrite(izquierda, LOW);
            digitalWrite(derecha, LOW); 
    }
    client.print("<!DOCTYPE html><html>");
    client.print("<head><meta name=\"viewport\"content=\"width=device-width, initial-scale=1\">");
    client.print("<link rel=\"icon\" herf=\"data:,\">");
    client.print("
   }

}
