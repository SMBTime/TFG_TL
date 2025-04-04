#include "file_manager.hpp"

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Escribiendo en el fichero: %s\r\n", path);
  #if defined(ESP8266)
    File file = fs.open(path, "w");
  #else
    File file = fs.open(path, FILE_WRITE);
  #endif
  if(!file){
    Serial.println("- ERROR: No se ha podido abrir el fichero\n");
    return;
  }
  if(file.println(message)){
    Serial.println("- Escritura correcta");
  } else {
    Serial.println("- write failed");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\r\n", path);
  #if defined(ESP8266)
    File file = fs.open(path, "a");
  #else
    File file = fs.open(path, FILE_APPEND);
  #endif
    if(!file){
        Serial.println("- failed to open file for appending");
        return;
    }
    if(file.println(message)){
        Serial.println("- message appended");
    } else {
        Serial.println("- append failed");
    }
    file.close();
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\r\n", path);
  #if defined(ESP8266)
    File file = fs.open(path, "r");
  #else
    File file = fs.open(path);
  #endif
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }

    Serial.println("- read from file:");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
    Serial.println("\n");    
}

void deleteFile(fs::FS &fs, const char * path){
  Serial.printf("Deleting file: %s\r\n", path);
  if(fs.remove(path)){
    Serial.println("- file deleted");
  } else {
    Serial.println("- delete failed");
  }
}

String readLineFromFile(fs::FS &fs, const char *path, int lineNumber) {
    Serial.printf("Leyendo la línea %d del fichero: %s\r\n", lineNumber, path);
  #if defined(ESP8266)
    File file = fs.open(path, "r");
  #else
    File file = fs.open(path);
  #endif
    if (!file || file.isDirectory()) {
        Serial.println("- ERROR: No se ha podido abrir el fichero para lectura");
        return "";
    }

    String line = "";
    int currentLine = 0;

    while (file.available()) {
        line = file.readStringUntil('\n'); // Lee una línea del archivo
        if (currentLine == lineNumber) {  // Si es la línea deseada, la devolvemos
            file.close();
            return line;
        }
        currentLine++;
    }

    file.close();
    Serial.println("- ERROR: La línea especificada no existe en el fichero");
    return ""; // Retorna vacío si no encontró la línea
}

int countLinesInFile(fs::FS &fs, const char *path) {
    Serial.printf("Contando líneas en el fichero: %s\r\n", path);
  #if defined(ESP8266)
    File file = fs.open(path, "r");
  #else
    File file = fs.open(path);
  #endif

    if (!file || file.isDirectory()) {
        Serial.println("- ERROR: No se ha podido abrir el fichero para lectura");
        return -1;  // Retorna -1 si hay un error
    }

    int lineCount = 0;
    while (file.available()) {
        file.readStringUntil('\n'); // Lee línea por línea
        lineCount++;
    }

    file.close();
    Serial.printf("- Número total de líneas: %d\n", lineCount);
    return lineCount;
}