#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

File myFile;

// put function declarations here:
int myFunction(int, int);
#define SS 40
void setup() {
  Serial.begin(9600);
  SPI.begin(37,38,36);
  Serial.print("Iniciando SD ...");
  //begin(SS, SPI, 4000000, "/sd", 5, true);
  if (!SD.begin(SS, SPI, 4000000, "/sd", 5, true)) {
  Serial.println("No se pudo inicializar");
  return;
  }
  Serial.println("inicializacion exitosa");
  myFile = SD.open("archivo.txt");//abrimos el archivo
  if (myFile) {
  Serial.println("archivo.txt:");
  while (myFile.available()) {
  Serial.write(myFile.read());
  }
  myFile.close(); //cerramos el archivo
  } else {
  Serial.println("Error al abrir el archivo");
  }
}

void loop() {
  
}