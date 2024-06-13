# PRACTICA6

## Codi sencer
```cpp
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
```

## Explicació del codi per parts
### Biblioteques
```cpp
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
```
Aquestes línies inclouen les llibreries necessàries per utilitzar l'ecosistema d'Arduino, la interfície SPI (Serial Peripheral Interface) per a la comunicació amb la targeta SD, i la llibreria SD per a la manipulació de fitxers en la targeta SD.

### Definició de variables
```cpp
File myFile;
#define SS 40
```
- myFile és un objecte de la classe File que s'utilitzarà per manipular els fitxers a la targeta SD.
- SS és una constant que defineix el pin de selecció de xip (CS) que s'utilitzarà per a la comunicació SPI amb la targeta SD.

### Setup
```cpp
void setup() {
  Serial.begin(9600);
  SPI.begin(37, 38, 36);
  Serial.print("Iniciando SD ...");
```
- Serial.begin(9600) inicia la comunicació sèrie amb una velocitat de 9600 bauds.
- SPI.begin(37, 38, 36) inicia la interfície SPI especificant els pins per MISO, MOSI, i SCK respectivament.
- Serial.print("Iniciando SD ...") escriu un missatge a la consola sèrie per indicar l'inici del procés d'inicialització de la SD.

### Inicialització de la Targeta SD
```cpp
  if (!SD.begin(SS, SPI, 4000000, "/sd", 5, true)) {
    Serial.println("No se pudo inicializar la tarjeta SD.");
    return;
  }
  Serial.println("Inicialización exitosa.");
```
- SD.begin(SS, SPI, 4000000, "/sd", 5, true) inicialitza la targeta SD utilitzant el pin de selecció de xip definit per SS, l'objecte SPI, una velocitat de 4 MHz, i altres paràmetres opcionals. Si la inicialització falla, imprimeix "No se pudo inicializar la tarjeta SD." i retorna del setup, finalitzant l'execució.
- Si la inicialització és correcta, imprimeix "Inicialización exitosa.".

### Crear i Escriure un Fitxer
```cpp
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
```
- myFile = SD.open("/archivo_copiado.txt", FILE_WRITE) obre (o crea si no existeix) el fitxer "archivo_copiado.txt" en mode escriptura.
- Si el fitxer s'obre correctament, imprimeix "Archivo creado correctamente." i escriu dues línies de text al fitxer.
- Després de l'escriptura, tanca el fitxer amb myFile.close() i imprimeix "Datos escritos correctamente en el archivo.".
- Si no es pot crear el fitxer, imprimeix "Error al crear el archivo en la tarjeta SD.".

 ### Obrir i Llegir un Fitxer Existent
 ```cpp
  myFile = SD.open("/archivo_original.txt");
  if (myFile) {
    Serial.println("/archivo_original.txt");
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
  } else {
    Serial.println("Error al abrir el archivo.");
  }
}
```
- myFile = SD.open("/archivo_original.txt") obre el fitxer "archivo_original.txt" en mode lectura.
- Si el fitxer s'obre correctament, imprimeix "/archivo_original.txt" i llegeix i escriu el contingut del fitxer caràcter per caràcter a la consola sèrie.
- Després de la lectura, tanca el fitxer amb myFile.close().
- Si no es pot obrir el fitxer, imprimeix "Error al abrir el archivo.".

### Loop
```cpp
void loop() {
 
}
```
El loop està buit, ja que tota la funcionalitat es realitza en el setup i no hi ha res que s'hagi de fer repetidament.
