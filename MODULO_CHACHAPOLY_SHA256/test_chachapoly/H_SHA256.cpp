#include "Print.h"
#include "H_SHA256.hpp"
// Instancia global de SHA256
SHA256 hash;

// Variables globales, Nonce, IV y Clave.
uint8_t sha_nonce[SHA_NONCE_SIZE];
uint8_t sha_iv[SHA_IV_SIZE];
uint8_t sha_key[SHA_KEY_SIZE];

// Contraseña usada como entrada para la derivación de claves
// Nota: Se recomienda cambiarla por otra que sea mas robusta, esta es un ejemplo. 
const char* password = "Este es mi primer TFG.";


void generateSHA_Nonce(void) {
  unsigned long timeSeed;
  Serial.println("Generando Nonce...");

  for (size_t i = 0; i < SHA_NONCE_SIZE; i++) {
    timeSeed = micros()+random(0,256);
    sha_nonce[i] = timeSeed;
    Serial.print(sha_nonce[i], HEX);
    Serial.print(" ");
  }
  Serial.println(); 
}


void generateSHA_IV(void) {
  generateSHA_Nonce();

  hash.reset();
  hash.update(sha_nonce, SHA_NONCE_SIZE);
  hash.finalize(sha_iv, SHA_IV_SIZE);

  Serial.println("Generando IV...");
  for (size_t i = 0; i < SHA_IV_SIZE; i++) {
    Serial.print(sha_iv[i], HEX);
    Serial.print(" ");
  }
  Serial.println(); 
}


void generateSHA_Key(void){
  generateSHA_IV();

  hash.reset();
  hash.update((const uint8_t*)password, strlen(password));
  hash.update(sha_iv, SHA_IV_SIZE);
  hash.update(sha_nonce, SHA_NONCE_SIZE);  
  hash.finalize(sha_key, SHA_KEY_SIZE);
  
  Serial.println("Generando clave ..."); 
  for (size_t i = 0; i < SHA_KEY_SIZE; i++) {
    Serial.print(sha_key[i], HEX);
    Serial.print(" ");
  }
  Serial.println(); 
}

