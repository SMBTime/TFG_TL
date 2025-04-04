#ifndef ascon_hpp
#define ascon_hpp

#include <Crypto.h>
#include <Ascon128.h>
#include "Shake128.hpp"

// Tamaños definidos según estándares NIST.
#define ASCON_TAG_SIZE 16
extern uint8_t ascon_tag[ASCON_TAG_SIZE];  

/**
 * @brief Genera la información necesaria para ASCON (clave y IV)
 */
void genasconsInfo(void);

/**
 * @brief Cifra datos usando ASCON-128.
 *        Configura la clave y IV, cifra los datos y calcula el tag de autenticación.
 * @param plaintext Puntero a los datos a cifrar
 * @param length Longitud de los datos a cifrar
 * @param ciphertext Buffer para almacenar el resultado cifrado
 */
void encryptAscon128(const uint8_t *plaintext, size_t length, uint8_t *ciphertext);

/**
 * @brief Descifra datos usando ASCON-128
 *        Configura la clave y IV, descifra los datos y verifica el tag de autenticación.
 * @param ciphertext Puntero a los datos cifrados
 * @param length Longitud de los datos cifrados
 * @param plaintext Buffer para almacenar el resultado descifrado
 * @return true si la autenticación fue exitosa, false en caso contrario
 */
bool decryptAscon128(const uint8_t *ciphertext, size_t length, uint8_t *plaintext);

#endif