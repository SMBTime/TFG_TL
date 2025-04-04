#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <Arduino.h>
#include "FS.h"
#include "LittleFS.h"

//Crea/Escribe un nuevo fichero.
void writeFile(fs::FS &fs, const char * path, const char * message);
//Añade contenido a un fichero.
void appendFile(fs::FS &fs, const char * path, const char * message);
// Lee el contenido de un fichero.
void readFile(fs::FS &fs, const char * path);
// Elimina un fichero.
void deleteFile(fs::FS &fs, const char * path);
//Devuelve una linea concreta del fichero.
String readLineFromFile(fs::FS &fs, const char *path, int lineNumber);
//Devuelve el nuemro de lineas que contiene el fichero.
int countLinesInFile(fs::FS &fs, const char *path);
#endif // FILE_MANAGER_H
