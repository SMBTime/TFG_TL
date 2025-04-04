#ifndef shake128_hpp
#define shake128_hpp

#include <Arduino.h>
#include <Crypto.h>
#include <XOF.h>
#include <SHAKE.h>
#include <string.h>

// Tamaños definidos según estándares NIST para Nonce IV y clave.
#define SHAKE_NONCE_SIZE 16
#define ASCON_IV_SIZE    16
#define ASCON_KEY_SIZE   16

// Variables globales para usar una vez generadas.
extern uint8_t shake_nonce[SHAKE_NONCE_SIZE];
extern uint8_t ascon_iv[ASCON_IV_SIZE];
extern uint8_t ascon_key[ASCON_KEY_SIZE];

/**
 * @brief Genera un nonce pseudoaleatorio usando el tiempo de ejecución.
 *        El nonce se genera combinando el tiempo de ejecución en microsegundos
 *        con valores aleatorios. Se imprime en hexadecimal por el puerto serial.
 */
void generateShake_Nonce(void);

/**
 * @brief Genera una clave segura usando SHAKE128.
 *        Utiliza el nonce generado para derivar tanto el vector de inicialización
 *        como la clave para ASCON. Imprime la clave resultante por el puerto serial.
 */
void generateShake_Key(void);

#endif