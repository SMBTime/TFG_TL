/**
 * @file procesado_archivos.ino
 * @brief Ejemplo de uso de funciones de manejo de archivos con LittleFS.
 *
 * Este sketch demuestra cómo utilizar funciones de gestión de archivos definidas en 
 * 'file_manager.hpp', incluyendo escritura, lectura, añadir de líneas, lectura de líneas 
 * específicas, y eliminación de archivos. Usa el sistema de archivos LittleFS para 
 * almacenamiento persistente en dispositivos compatibles como ESP8266 o ESP32.
 * 
 * Es necesario tener la herramienta de LittleFS previamente instalada.
 *
 * @author Hugo Sánchez
 */
#include "file_manager.hpp"

// Variable para almacenar una línea leída del archivo
String datos;

void setup() {
  // Espera inicial para asegurar estabilidad del sistema
  delay(2000);
  Serial.begin(115200);

  // Monta el sistema de archivos LittleFS.
  if (!LittleFS.begin()) {
    Serial.println("Fallo al montar LittleFS");
    return;
  } else {
    Serial.println("Little FS configurado correctamente");
  }

  // Prueba de lectura de un fichero subido mediante LittleFS.
  readFile(LittleFS, "/Prueba.txt");
  
  //Prueba de creación de un nuevo fichero, escritura le cutra y eliminación de un fichero.
  writeFile(LittleFS, "/Test.txt","Esto es otra linea añadida al fichero.");
  appendFile(LittleFS, "/Test.txt", "Esto es una prueba de escritura");
  readFile(LittleFS, "/Test.txt");
  readLineFromFile(LittleFS, "/Test.txt",countLinesInFile(LittleFS, "/Test.txt")-1,datos);
  Serial.println(datos);
  deleteFile(LittleFS, "/Test.txt");  
}

void loop() {

}