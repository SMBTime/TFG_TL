#include "Shake128.hpp"

// Instancia de SHAKE128
SHAKE128 shake128;

uint8_t shake_nonce[SHAKE_NONCE_SIZE];
uint8_t ascon_iv[ASCON_IV_SIZE];
uint8_t ascon_key[ASCON_KEY_SIZE];

void generateShake_Nonce(void) {
  unsigned long timeSeed;
  Serial.println("Generando Nonce...");

  for (size_t i = 0; i < SHAKE_NONCE_SIZE; i++) {
    timeSeed = micros() + random(0, 256);
    shake_nonce[i] = timeSeed;
    Serial.print(shake_nonce[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}


void generateShake_Key(void) {
  Serial.println("Generando clave con Shake...");

  generateShake_Nonce();
  
  shake128.reset();
  shake128.update(shake_nonce, SHAKE_NONCE_SIZE);
  shake128.extend(ascon_iv, ASCON_IV_SIZE);
  shake128.extend(ascon_key, ASCON_KEY_SIZE);
  
  //Comentar si no es necesario verificar el contenido.
  Serial.println("VI generado:");
  for (size_t i = 0; i < ASCON_IV_SIZE; i++) {
    Serial.print(ascon_iv[i], HEX);
    Serial.print(" ");
  }
  Serial.println("Clave derivada:");
  for (size_t i = 0; i < ASCON_KEY_SIZE; i++) {
    Serial.print(ascon_key[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}
