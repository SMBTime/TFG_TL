#include "ChaCha20Poly.hpp"

ChaChaPoly chacha;

uint8_t chacha_tag[CHACHA_TAG_SIZE];  

void genchachaInfo(void){
  generateSHA_Key();
}

void encryptChaChaPoly(const uint8_t *plaintext, size_t length, uint8_t *ciphertext) {
  Serial.println("Iniciando cifrado ChaChaPoly...");


  chacha.setKey(sha_key, SHA_KEY_SIZE);
  chacha.setIV(sha_iv, SHA_IV_SIZE);


  chacha.addAuthData(sha_nonce, SHA_NONCE_SIZE);


  chacha.encrypt(ciphertext, plaintext, length);


  chacha.computeTag(chacha_tag, CHACHA_TAG_SIZE);

 
  //Comentar si no es necesario verificar funcionamiento.
  Serial.println("Cifrado completado. Texto cifrado:");
  for (size_t i = 0; i < length; i++) {
    Serial.print(ciphertext[i], HEX);
    Serial.print(" ");
  }
  Serial.println("\nTag de autenticación:");
  for (size_t i = 0; i < CHACHA_TAG_SIZE; i++) {
    Serial.print(chacha_tag[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

bool decryptChaChaPoly(const uint8_t *ciphertext, size_t length, uint8_t *plaintext) {
  Serial.println("Iniciando descifrado ChaChaPoly...");

  chacha.setKey(sha_key, SHA_KEY_SIZE);
  chacha.setIV(sha_iv, SHA_IV_SIZE);

  // Agregar datos autenticados
  chacha.addAuthData(sha_nonce, SHA_NONCE_SIZE);

  // Descifrar los datos
  chacha.decrypt(plaintext, ciphertext, length);

  // Verificar el TAG de autenticación
  if (chacha.checkTag(chacha_tag, CHACHA_TAG_SIZE)) {
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
