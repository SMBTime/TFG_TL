#include "AESGCM.hpp"

// Instancia global de AES-GCM
GCM<AES256> aes_gcm;

extern uint8_t hkdf_nonce[HKDF_NONCE_SIZE];
extern uint8_t hkdf_iv[HKDF_IV_SIZE];
extern uint8_t hkdf_key[HKDF_KEY_SIZE];

// Tag de autenticación para GCM
uint8_t aesgcm_tag[AESGCM_TAG_SIZE]; 

void genaesgcmInfo(void){
  generateHKDF_Key();
}

void encryptAES_GCM(const uint8_t *plaintext, size_t length, uint8_t *ciphertext) {
  Serial.println("Iniciando cifrado AES-GCM...");

  // Inicializar AES-GCM con la clave y IV de HKDF
  aes_gcm.setKey(hkdf_key, AES_KEY_SIZE);
  aes_gcm.setIV(hkdf_iv, AES_IV_SIZE);

  // Cifrado del mensaje
  aes_gcm.encrypt(ciphertext, plaintext, length);

  // Calculo del TAG de autenticación.
  aes_gcm.computeTag(aesgcm_tag, AESGCM_TAG_SIZE);
  
  //Comentar si no ser quiere verificar funcionamiento.
  Serial.println("Cifrado completado. Texto cifrado:");
  for (size_t i = 0; i < length; i++) {
    Serial.print(ciphertext[i], HEX);
    Serial.print(" ");
  }
  Serial.println("\nTag de autenticación:");
  for (size_t i = 0; i < AESGCM_TAG_SIZE; i++) {
    Serial.print(aesgcm_tag[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  
}

// Función de descifrado AES-GCM
bool decryptAES_GCM(const uint8_t *ciphertext, size_t length, uint8_t *plaintext) {
  Serial.println("Iniciando descifrado AES-GCM...");

  // Inicializar AES-GCM con la clave y IV de HKDF
  aes_gcm.setKey(hkdf_key, AES_KEY_SIZE);
  aes_gcm.setIV(hkdf_iv, AES_IV_SIZE);

  // Descifrar el mensaje
  aes_gcm.decrypt(plaintext, ciphertext, length);

  // Verificar el TAG de autenticación
  if (aes_gcm.checkTag(aesgcm_tag, AESGCM_TAG_SIZE)) {
    //Comentar si no es necesario visualizaralo.
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


