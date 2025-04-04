#ifndef tiempo_hpp
#define tiempo_hpp

#include <stdbool.h>
#include <Arduino.h>
#include <stdio.h>

/**
 * @brief Inicializa el temporizador guardando el tiempo actual.
 * 
 * Esta función debe ser llamada antes de cualquier medición de tiempo.
 */
void init_temp(void);

/**
 * @brief Obtiene el tiempo transcurrido desde la inicialización.
 * 
 * @param ms Si es true, el tiempo se devuelve en milisegundos. Si es false, se devuelve en microsegundos.
 * @return float Tiempo transcurrido desde la llamada a `init_temp`.
 */
float get_temp(bool ms);

#endif