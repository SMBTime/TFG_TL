#include "tiempo.hpp"

// Variable global para almacenar el tiempo de inicio en microsegundos.
uint32_t t_inicio=0;

void init_temp(void) {
  t_inicio=micros();
}

float get_temp(bool ms) {
  float t=0;
  
  t=micros()-t_inicio;

  if(ms){
    // Convertir a milisegundos
    return t/1e3; 
  }
  // Tiempo en microsegundos
  return t; 
}





