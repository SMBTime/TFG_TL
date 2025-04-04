#ifndef aesgcm_hpp
#define aesgcm_hpp

#include <AES.h>
#include <GCM.h>
#include "M_HKDF.hpp"

// Definiciones de tamaños para AES-GCM
#define AES_KEY_SIZE 32      // Tamaño de la clave AES (256 bits)
#define AES_IV_SIZE 12       // Tamaño del IV recomendado para GCM (96 bits)
#define AESGCM_TAG_SIZE 16          // Tamaño del Tag de autenticación (128 bits)

// Variable global para el tag de autenticación GCM
extern uint8_t aesgcm_tag[AESGCM_TAG_SIZE];

/**
 * @brief Genera la información necesaria para AES-GCM (clave, IV y nonce)
 */
void genaesgcmInfo(void);

/**
 * @brief Cifra un mensaje usando AES-GCM
 *
 * @param plaintext Puntero al mensaje en claro
 * @param length Longitud del mensaje
 * @param ciphertext Buffer de salida para el texto cifrado
 */
void encryptAES_GCM(const uint8_t *plaintext, size_t length, uint8_t *ciphertext);

/**
 * @brief Descifra un mensaje usando AES-GCM
 *
 * @param ciphertext Puntero al texto cifrado
 * @param length Longitud del texto cifrado
 * @param plaintext Buffer de salida para el mensaje descifrado
 * @return true si la autenticación fue exitosa, false en caso contrario
 */
bool decryptAES_GCM(const uint8_t *ciphertext, size_t length, uint8_t *plaintext);

#endif