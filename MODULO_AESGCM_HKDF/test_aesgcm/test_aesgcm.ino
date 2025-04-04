/**
 * @brief Función de configuración inicial
 * 
 * Este código de prueba demuestra el uso del cifrado AES-GCM:
 * 1. Genera los componentes criptográficos necesarios
 * 2. Cifra un mensaje de prueba
 * 3. Descifra el mensaje
 * 4. Verifica la autenticidad del mensaje
 */
#include "AESGCM.hpp"

// Longitud máxima de cada línea de texto
#define MAX_LINE_LENGTH 128   

void setup() {
  // Espera para la inicialización del hardware
  delay(1000);
  Serial.begin(115200);
  
  // Mensaje de prueba
  const char* mensaje = "Hola, este es un mensaje de prueba !";
  // Buffers para los datos cifrados y descifrados
  uint8_t encryptedData[MAX_LINE_LENGTH];
  uint8_t decryptedData[MAX_LINE_LENGTH];

  // Genera la información criptográfica necesaria
  genaesgcmInfo();

  // Cifrado
  encryptAES_GCM((uint8_t*)mensaje, strlen(mensaje), encryptedData);

  // Descifrado
  decryptAES_GCM(encryptedData, strlen(mensaje), decryptedData);
 
}

void loop() {

}
