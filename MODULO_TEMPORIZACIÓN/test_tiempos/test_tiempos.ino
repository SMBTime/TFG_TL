/**
 * @file test_tiempos.ino
 * @brief Ejemplo de uso de la librería de medición de tiempos.
 *
 * Esta prueba mide el tiempo transcurrido entre una llamada a init_temp() y un delay posterior, 
 * usando la función get_temp() para obtener el resultado en milisegundos o microsegundos.
 *
 * @author Hugo Sánchez
 */
#include "tiempo.hpp"

// Variable global para almacenar el tiempo medido
float resultado=0;

void setup() {
  // Inicializa la comunicación serie 
  Serial.begin(115200);
  init_temp();
  delay(10);
}

void loop() {

  // Ejemplo 1: medir un retardo de 10 ms en ms y us
  init_temp();
  delay(10); 
  resultado=get_temp(true);
  Serial.println("Tiempo en ms:");
  Serial.println(resultado);
  delay(1000);

  init_temp();
  delay(10); 
  resultado=get_temp(false);
  Serial.println("Tiempo en us:");
  Serial.println(resultado);
  delay(1000);

  // Ejemplo 2: medir un retardo de 1 ms en ms y us
  init_temp();
  delay(1); 
  resultado=get_temp(true);
  Serial.println("Tiempo en ms:");
  Serial.println(resultado);
  delay(1000);

  init_temp();
  delay(1); 
  resultado=get_temp(false);
  Serial.println("Tiempo en us:");
  Serial.println(resultado);
  delay(1000);

  // Ejemplo 3: medir un retardo de 100 ms en ms y us
  init_temp();
  delay(100); 
  resultado=get_temp(true);
  Serial.println("Tiempo en ms:");
  Serial.println(resultado);
  delay(1000);

  init_temp();
  delay(100); 
  resultado=get_temp(false);
  Serial.println("Tiempo en us:");
  Serial.println(resultado);
  delay(1000);
}
