#ifndef h_sha256_hpp
#define h_sha256_hpp

#include <Arduino.h>
#include <Crypto.h>
#include <SHA256.h>

// Tamaños definidos
#define SHA_NONCE_SIZE 8  // Tamaño del nonce
#define SHA_IV_SIZE    12 // Tamaño del vector de inicialización
#define SHA_KEY_SIZE   32 // Tamaño de la clave 

extern uint8_t sha_nonce[SHA_NONCE_SIZE];
extern uint8_t sha_iv[SHA_IV_SIZE];
extern uint8_t sha_key[SHA_KEY_SIZE];

/**
 * @brief Genera un nonce pseudoaleatorio usando el tiempo de ejecución y números aleatorios.
*/
void generateSHA_IV(void);


/**
 * @brief Genera el vector de inicialización (IV) aplicando SHA-256 al nonce.
*/
void generateSHA_Nonce(void);


/**
 * @brief Genera todos los componentes (nonce, IV y clave).
*/
void generateSHA_Key(void);

#endif