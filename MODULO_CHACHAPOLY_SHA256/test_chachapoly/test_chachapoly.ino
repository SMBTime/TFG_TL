#include "ChaCha20Poly.hpp"

// Longitud máxima de cada línea de texto
#define MAX_LINE_LENGTH 128   

void setup() {
  delay(1000);
  Serial.begin(115200);

  const char* mensaje = "Hola, este es un mensaje de prueba !";
  uint8_t encryptedData[MAX_LINE_LENGTH];
  uint8_t decryptedData[MAX_LINE_LENGTH];

  Serial.println("\n");
  // Generar información necesaria para el cifrado.
  genchachaInfo();

  //Cifrado.
  encryptChaChaPoly((uint8_t*)mensaje, strlen(mensaje), encryptedData);

  //Descifrado.
  decryptChaChaPoly(encryptedData, strlen(mensaje), decryptedData);
}

void loop() {

}