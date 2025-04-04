#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <Arduino.h>
#include "FS.h"
#include "LittleFS.h"

/**
 * @brief Crea/Escribe un nuevo fichero.
 *
 * @param fs Sistema de archivos.
 * @param path Ruta del fichero.
 * @param message Contenido a escribir.
 */
void writeFile(fs::FS &fs, const char * path, const char * message);

/**
 * @brief Añade contenido a un fichero existente.
 *
 * @param fs Sistema de archivos.
 * @param path Ruta del fichero.
 * @param message Contenido a añadir.
 */
void appendFile(fs::FS &fs, const char * path, const char * message);

/**
 * @brief Lee y muestra el contenido de un fichero por el puerto serial.
 *
 * @param fs Sistema de archivos.
 * @param path Ruta del fichero.
 */
void readFile(fs::FS &fs, const char * path);

/**
 * @brief Elimina un fichero.
 *
 * @param fs Sistema de archivos.
 * @param path Ruta del fichero a eliminar.
 */
void deleteFile(fs::FS &fs, const char * path);

/**
 * @brief Lee una línea específica de un fichero.
 *
 * @param fs Sistema de archivos.
 * @param path Ruta del fichero.
 * @param lineNumber Número de línea a leer.
 * @param outLine String donde se almacenará la línea leída.
 * @return true si la línea fue leída correctamente, false en caso contrario.
 */
bool readLineFromFile(fs::FS &fs, const char *path, int lineNumber,String &outLine);

/**
 * @brief Cuenta el número de líneas en un fichero.
 *
 * @param fs Sistema de archivos (ej. LittleFS).
 * @param path Ruta del fichero.
 * @return Número de líneas o -1 si hay error.
 */
int countLinesInFile(fs::FS &fs, const char *path);

#endif
