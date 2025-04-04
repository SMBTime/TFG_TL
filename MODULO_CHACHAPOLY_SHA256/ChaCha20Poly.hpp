#ifndef chacha20poly_hpp
#define chacha20poly_hpp

#include "H_SHA256.hpp"
#include <Crypto.h>
#include <ChaChaPoly.h>
#include <string.h>

// Tag de autenticación para CHACHAPOLY
#define CHACHA_TAG_SIZE 16
extern uint8_t chacha_tag[CHACHA_TAG_SIZE];  

/**
 * @brief Genera la información necesaria para ChaChaPoly (clave, IV y nonce)
 */
void genchachaInfo(void);

/**
 * @brief Cifra un mensaje usando ChaChaPoly
 *
 * @param plaintext Puntero al mensaje en claro
 * @param length Longitud del mensaje
 * @param ciphertext Buffer de salida para el texto cifrado
 */
void encryptChaChaPoly(const uint8_t *plaintext, size_t length, uint8_t *ciphertext);

/**
 * @brief Descifra un mensaje usando ChaChaPoly
 *
 * @param ciphertext Puntero al texto cifrado
 * @param length Longitud del texto cifrado
 * @param plaintext Buffer de salida para el mensaje descifrado
 * @return true si la autenticación fue exitosa, false en caso contrario
 */
bool decryptChaChaPoly(const uint8_t *ciphertext, size_t length, uint8_t *plaintext);


#endif