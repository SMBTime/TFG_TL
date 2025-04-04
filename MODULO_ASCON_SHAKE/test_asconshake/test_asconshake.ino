/**
 * @file test_asconshake.ino
 * @brief Programa de prueba para el cifrado/descifrado con ASCON y SHAKE128
 * @author Hugo Sánchez
 */
#include "Ascon.hpp"

// Longitud máxima de cada línea de texto
#define MAX_LINE_LENGTH 64   

void setup() {
  delay(1000);
  Serial.begin(115200);

  const char* mensaje = "Hola, este es un mensaje de prueba :) !";
  uint8_t encryptedData[MAX_LINE_LENGTH];
  uint8_t decryptedData[MAX_LINE_LENGTH];

  Serial.println("\n");
  // Generar información necesaria para el cifrado.
  genasconsInfo();

  //Cifrado.
  encryptAscon128((uint8_t*)mensaje, strlen(mensaje), encryptedData);

  //Descifrado.
  decryptAscon128(encryptedData, strlen(mensaje), decryptedData);
}

void loop() {

}
