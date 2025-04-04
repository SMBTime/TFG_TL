#include "file_manager.hpp"

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Escribiendo en el fichero: %s\r\n", path);

  //Distinta función dependiendo del ESP.
  #if defined(ESP8266)
    File file = fs.open(path, "w");
  #else
    File file = fs.open(path, FILE_WRITE);
  #endif

  if(!file){
    Serial.println("- ERROR: No se ha podido abrir el fichero.\n");
    return;
  }

  if(file.println(message)){
    Serial.println("- Escritura correcta.");
  } else {
    Serial.println("- Error en la escritura.");
  }

  file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Agregando datos al fichero: %s\r\n", path);

  //Distinta función dependiendo del ESP.
  #if defined(ESP8266)
    File file = fs.open(path, "a");
  #else
    File file = fs.open(path, FILE_APPEND);
  #endif

  if(!file){
    Serial.println("- Error al abrir el fichero.");
    return;
  }

  if(file.println(message)){
    Serial.println("-Datos agregados.");
  } else {
    Serial.println("- Error al agregar.");
  }

  file.close();
}

void readFile(fs::FS &fs, const char * path){
  Serial.printf("Leyendo fichero: %s\r\n", path);

  //Distinta función dependiendo del ESP.
  #if defined(ESP8266)
    File file = fs.open(path, "r");
  #else
    File file = fs.open(path);
  #endif

  if(!file || file.isDirectory()){
    Serial.println("- Error al abrir el fichero.");
    return;
  }

  Serial.println("- datos leidos:");
  while(file.available()){
    Serial.write(file.read());
  }

  file.close();
  Serial.println("\n");    
}

void deleteFile(fs::FS &fs, const char * path){
  Serial.printf("Eliminando fichero: %s\r\n", path);

  if(fs.remove(path)){
    Serial.println("- Fichero eliminado.");
  } else {
    Serial.println("-Error al eliminar.");
  }
}

bool readLineFromFile(fs::FS &fs, const char *path, int lineNumber,String &outLine) {
  Serial.printf("Leyendo la línea %d del fichero: %s\r\n", lineNumber, path);
  String line = "";
  int currentLine = 0;

  //Distinta función dependiendo del ESP.
  #if defined(ESP8266)
    File file = fs.open(path, "r");
  #else
    File file = fs.open(path);
  #endif

  if (!file || file.isDirectory()) {
    Serial.println("- ERROR: No se ha podido abrir el fichero para lectura");
    return false;
  }

  while (file.available()) {
    line = file.readStringUntil('\n'); 
    if (currentLine == lineNumber) { 
      file.close();
      outLine=line;
      return true;
    }
    currentLine++;
  }

  file.close();
  Serial.println("- Error, la línea especificada no existe en el fichero");
  return false; 
}

int countLinesInFile(fs::FS &fs, const char *path) {
  Serial.printf("Contando líneas en el fichero: %s\r\n", path);
  int lineCount = 0;

  //Distinta función dependiendo del ESP.
  #if defined(ESP8266)
    File file = fs.open(path, "r");
  #else
    File file = fs.open(path);
  #endif

  if (!file || file.isDirectory()) {
    Serial.println("- Error al abrir el fichero.");
    return -1;  // Retorna -1 si hay un error
  }

  while (file.available()) {
    file.readStringUntil('\n'); // Lee línea por línea
    lineCount++;
  }

  file.close();
  Serial.printf("- Numero total de lineas: %d\n", lineCount);
  return lineCount;
}