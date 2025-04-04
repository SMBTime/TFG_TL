#include "M_HKDF.hpp"

// Instancia global de SHA256
HKDF<SHA256> hkdf_der;
SHA256 sha;
// Variables globales, Nonce, IV y Clave.
uint8_t hkdf_nonce[HKDF_NONCE_SIZE];
uint8_t hkdf_iv[HKDF_IV_SIZE];
uint8_t hkdf_key[HKDF_KEY_SIZE];
bool nonce_generada=false, iv_generado=false;

// Contraseña usada como entrada para la derivación de claves
// Nota: Se recomienda cambiarla por otra que sea mas robusta, esta es un ejemplo. 
const char* password = "Este es mi primer TFG.";


void generateHKDF_Nonce(void){
  Serial.println("Generando Nonce...");
  unsigned long timeSeed;

  for (size_t i = 0; i < HKDF_NONCE_SIZE; i++) {
    timeSeed = micros() + random(0, 256);
    hkdf_nonce[i] = timeSeed;
    Serial.print(hkdf_nonce[i], HEX);
    Serial.print(" ");
  }
  nonce_generada=true;
  Serial.println();
}


void generateHKDF_IV(void) {
  // Asegura que tenemos un nonce antes de continuar.
  if(!nonce_generada){
    generateHKDF_Nonce();
  }
  
  //Generación del IV a partir del hash de SHA-256.
  sha.reset();
  sha.update(hkdf_nonce, HKDF_NONCE_SIZE);
  sha.finalize(hkdf_iv, HKDF_IV_SIZE);

  //Comentar si no es necesario visualizarlo.
  Serial.println("Generando IV...");
  for (size_t i = 0; i < HKDF_IV_SIZE; i++) {
    Serial.print(hkdf_iv[i], HEX);
    Serial.print(" ");
  }

  iv_generado=true;
  Serial.println();
}


void generateHKDF_Key(void) {
  Serial.println("Generando clave con HKDF...");
  // Asegura que tenemos el IV antes de continuar.
  if(!iv_generado){
    generateHKDF_IV();
  }

  // Configura HKDF con la contraseña y el IV generado (que actua como salt).
  hkdf_der.setKey(password,sizeof(password),hkdf_iv, HKDF_IV_SIZE);

  // Extrae y expande la clave (contraseña) derivada.
  hkdf_der.extract(hkdf_key,HKDF_KEY_SIZE,password,sizeof(password));

  //Comentar si no es necesario visualizarlo.  
  Serial.println("Clave derivada:");
  for (size_t i = 0; i < HKDF_KEY_SIZE; i++) {
    Serial.print(hkdf_key[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

