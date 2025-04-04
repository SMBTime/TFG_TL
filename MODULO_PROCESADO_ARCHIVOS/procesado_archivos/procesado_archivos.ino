#include "file_manager.hpp"

int mydata;

void setup() {
  delay(2000);
  Serial.begin(115200);
  if (!LittleFS.begin()) {
    Serial.println("LittleFS Mount Failed");
    return;
  } else {
    Serial.println("Little FS Mounted Successfully");
  }
  readFile(LittleFS, "/Prueba.txt");
  writeFile(LittleFS, "/Test.txt","Esto es otra linea añadida al fichero.");
  appendFile(LittleFS, "/Test.txt", "Esto es una prueba de escritura");
  readFile(LittleFS, "/Test.txt");
  Serial.println(readLineFromFile(LittleFS, "/Test.txt",countLinesInFile(LittleFS, "/Test.txt")-1));
  deleteFile(LittleFS, "/Test.txt");  
}

void loop() {
}