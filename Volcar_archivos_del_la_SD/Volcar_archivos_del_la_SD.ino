#include "SD.h"

const int chipSelect = 5;

void setup() {

  // Abra las comunicaciones serie y espere a que se abra el puerto:

  Serial.begin(115200);

  // espere a que Serial Monitor se conecte. Necesario solo para placas de puertos USB nativos:

  while (!Serial);

  Serial.print("Inicializando tarjeta SD...");
  Serial.print("");

  if (!SD.begin(chipSelect)) {

    Serial.println("inicialización falló. Cosas para comprobar:");

    Serial.println("1. ¿Hay una tarjeta insertada?");

    Serial.println("2.¿Tu cableado es correcto?");

    Serial.println("3.¿Cambió el pin chipSelect para que coincida con su escudo o módulo?");

    Serial.println("Nota: presione reiniciar o vuelva a abrir este monitor en serie después de solucionar su problema!");

    while (true);

  }
  Serial.println("");
  Serial.println("inicialización hecha.");
  Serial.println("");

  // abre el archivo. tenga en cuenta que solo se puede abrir un archivo a la vez,

  // así que tienes que cerrar este antes de abrir otro.

  File dataFile = SD.open("datalog.txt");

  // si el archivo está disponible, escribe en él:

  if (dataFile) {

    while (dataFile.available()) {

      Serial.write(dataFile.read());

    }

    dataFile.close();

  }

  // si el archivo no está abierto, aparece un error:

  else {

    Serial.println("error al abrir datalog.txt");

  }
}

void loop() {
}
