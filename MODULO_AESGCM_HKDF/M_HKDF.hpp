#ifndef m_hkdf_hpp
#define m_hkdf_hpp

#include <Arduino.h>
#include <string.h>
#include <Crypto.h>
#include <SHA256.h>
#include <Hash.h>
#include <HKDF.h>

// Definiciones de tamaños para HKDF
#define HKDF_NONCE_SIZE 8   // Tamaño del nonce
#define HKDF_IV_SIZE    12  // Tamaño del vector de inicialización
#define HKDF_KEY_SIZE   32  // Tamaño de la clave derivada

// Variables globales para los componentes derivados
extern uint8_t hkdf_nonce[HKDF_NONCE_SIZE];
extern uint8_t hkdf_iv[HKDF_IV_SIZE];
extern uint8_t hkdf_key[HKDF_KEY_SIZE];

/**
 * @brief Genera un nonce pseudoaleatorio usando el tiempo de ejecución y números aleatorios.
*/
void generateHKDF_Nonce(void);

/**
 * @brief Genera el vector de inicialización (IV) aplicando SHA-256 al nonce.
*/
void generateHKDF_IV(void);

/**
 * @brief Genera todos los componentes (nonce, IV y clave).
*/
void generateHKDF_Key(void);

#endif