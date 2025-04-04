#include "tiempo.hpp"

float resultado=0;

void setup() {
  
  Serial.begin(115200);
  init_temp();
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
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
