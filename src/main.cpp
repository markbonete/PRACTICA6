#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

File myFile;
#define SS 40

void setup() {
  Serial.begin(9600);
  SPI.begin(37,38,36);
  Serial.print("Iniciando SD ...");
  //begin(SS, SPI, 4000000, "/sd", 5, true);
  if (!SD.begin(SS, SPI, 4000000, "/sd", 5, true)) {
    Serial.println("No se pudo inicializar la tarjeta SD.");
    return;;
  }
  
  
  Serial.println("Inicialización exitosa.");

  // Crear y escribir en el archivo en la tarjeta SD
  myFile = SD.open("/archivo_copiado.txt", FILE_WRITE);
  if (myFile) {
    Serial.println("Archivo creado correctamente.");

    // Escribir datos en el archivo
    myFile.println("¡Hola, mundo!");
    myFile.println("Este es un archivo de texto creado desde Arduino.");

    // Cerrar el archivo
    myFile.close();
    Serial.println("Datos escritos correctamente en el archivo.");
  } else {
    Serial.println("Error al crear el archivo en la tarjeta SD.");
  }

  // Abrir y leer el archivo original desde la tarjeta SD
  myFile = SD.open("/archivo_original.txt");//abrimos el archivo
  if (myFile) {
    Serial.println("/archivo_original.txt");
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close(); //cerramos el archivo
  } else {
    Serial.println("Error al abrir el archivo.");
  }
}

void loop() {
 
}