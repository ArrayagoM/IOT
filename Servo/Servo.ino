#include <ESP32Servo.h>

Servo myservo;

void setup() {
  Serial.begin(115200); 
  myservo.attach(27);

  myservo.write(0);

}

void loop() {
 
   myservo.write(90);
   Serial.print("90");
   Serial.print("");
  delay(2000);
  myservo.write(25);
  Serial.print("25");
  Serial.print("");
  delay(2000);
  myservo.write(90);
   Serial.print("90");
   Serial.print("");
  delay(2000);
myservo.write(160);
Serial.print("160");
Serial.print("");
delay(2000);
myservo.write(90);
Serial.print("90");
Serial.print("");
delay(2000);
myservo.write(25);
Serial.print("25");
Serial.print("");
delay(2000);
}
