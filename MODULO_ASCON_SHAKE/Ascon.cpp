#include "Ascon.hpp"

Ascon128 ascon;

extern uint8_t shake_nonce[SHAKE_NONCE_SIZE];
extern uint8_t ascon_iv[ASCON_IV_SIZE];
extern uint8_t ascon_key[ASCON_KEY_SIZE];

uint8_t ascon_tag[ASCON_TAG_SIZE]; 

void genasconsInfo(void){
  generateShake_Key();
}


void encryptAscon128(const uint8_t *plaintext, size_t length, uint8_t *ciphertext) {
  Serial.println("Iniciando cifrado Ascon128...");

  // Inicializar AES-GCM con la clave y IV de HKDF
  ascon.setKey(ascon_key, ASCON_KEY_SIZE);
  ascon.setIV(ascon_iv, ASCON_IV_SIZE);
  
  // Cifrar el mensaje
  ascon.encrypt(ciphertext, plaintext, length);

  // Obtener el TAG de autenticación
  ascon.computeTag(ascon_tag, ASCON_TAG_SIZE);
  
  //Comentar si no es necesario verificar funcionamiento.
  Serial.println("Cifrado completado. Texto cifrado:");
  for (size_t i = 0; i < length; i++) {
    Serial.print(ciphertext[i], HEX);
    Serial.print(" ");
  }
  Serial.println("\nTag de autenticación:");
  for (size_t i = 0; i < ASCON_TAG_SIZE; i++) {
    Serial.print(ascon_tag[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}


bool decryptAscon128(const uint8_t *ciphertext, size_t length, uint8_t *plaintext) {
  Serial.println("Iniciando descifrado Ascon128...");

  // Inicializar AES-GCM con la clave y IV de HKDF
  ascon.setKey(ascon_key, ASCON_KEY_SIZE);
  ascon.setIV(ascon_iv, ASCON_IV_SIZE);

  // Descifrar el mensaje
  ascon.decrypt(plaintext, ciphertext, length);

  // Verificar el TAG de autenticación
  if (ascon.checkTag(ascon_tag, ASCON_TAG_SIZE)) {
    //Comentar si no es necesario verificar el funcionamiento.
    Serial.println("Descifrado exitoso. Texto original:");
    for (size_t i = 0; i < length; i++) {
      Serial.print((char)plaintext[i]);
    }
    Serial.println();
    return true;
  } else {
    Serial.println("Error: Falló la autenticación del mensaje.");
    return false;
  }
}
