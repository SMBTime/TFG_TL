// Inclusión de librerías según la plataforma
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif

#include <WiFiUdp.h>
#include <Arduino.h>

//Datos del router usado
WiFiUDP udp;
unsigned int puerto = 1234;
const char* ssid = "TFG_WIFI";
const char* password = "TFG_TL_IoT";

// Parámetros Diffie-Hellman
// Usamos números pequeños por simplicidad
const uint32_t g = 5;
const uint32_t p = 23; 

//Datos de ejemplo para este módulo de pruebas
uint32_t privateKey;
uint32_t publicKey;
uint32_t sharedKey;

bool claveIntercambiada = false;

//Metodo para generar la clave pública.
uint32_t modexp(uint32_t base, uint32_t exp, uint32_t mod) {
    uint32_t result = 1;
    base = base % mod;
    while (exp > 0) {
      if (exp % 2 == 1){
        result = (uint64_t)result * base % mod;
      }
      exp = exp >> 1;
      base = (uint64_t)base * base % mod;
    }
    return result;
}

void setup() {
    Serial.begin(115200);

    // Conexión a la red WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConectado a WiFi");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
    
    // Inicialización del servidor UDP
    udp.begin(puerto);

    // Generación de claves con Diffie-Hellman
    privateKey = random(2, 10);
    publicKey = modexp(g, privateKey, p);

    Serial.print("Clave privada (server): ");
    Serial.println(privateKey);
    Serial.print("Clave pública (server): ");
    Serial.println(publicKey);
}

void loop() {
  char paquete[255];
  int tamanoPaquete = udp.parsePacket();
  if (tamanoPaquete) {
    int len = udp.read(paquete, 255);
    if (len > 0){
      paquete[len] = 0;
    }

    // Fase de intercambio de claves
    if (!claveIntercambiada) {
      uint32_t clientPublicKey = atoi(paquete);
      sharedKey = (uint32_t)pow(clientPublicKey, privateKey) % p;

      Serial.print("Clave pública recibida del cliente: ");
      Serial.println(clientPublicKey);
      Serial.print("Clave secreta compartida: ");
      Serial.println(sharedKey);

      // Envía la clave pública al cliente
      udp.beginPacket(udp.remoteIP(), udp.remotePort());
      udp.print(publicKey);
      udp.endPacket();

      claveIntercambiada = true;
    } else {
      // Fase de recepción de datos cifrados    
      Serial.println("Paquete recibido:");
      Serial.println(paquete);

      // Procesamiento del paquete (formato: clave;mensaje;tag)
      char* claveCifrada = strtok(paquete, ";");
      char* mensajeCifrado = strtok(NULL, ";");
      char* tag = strtok(NULL, ";");

      if (claveCifrada && mensajeCifrado && tag) {
        Serial.println("Clave cifrada:");
        Serial.println(claveCifrada);
        Serial.println("Mensaje cifrado:");
        Serial.println(mensajeCifrado);
        Serial.println("TAG:");
        Serial.println(tag);
      } else {
        Serial.println("Error en el formato del paquete.");
      }
    }
  }
}

