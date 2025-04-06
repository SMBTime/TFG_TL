// Compatibilidad con ESP32 y ESP8266
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif

#include <WiFiUdp.h>
#include <Arduino.h>

//Datos del router usado
// Si la IP no es estática haya que modificarla.
WiFiUDP udp;
unsigned int puerto = 1234;
const char* ssid = "TFG_WIFI";
const char* password = "TFG_TL_IoT";
const char* direccionIP = "192.168.101.177"; 

// Parámetros Diffie-Hellman
// Usamos números pequeños por simplicidad
const uint32_t g = 5;
const uint32_t p = 23;

//Datos recibidos de ejemplo para este módulo.
uint32_t privateKey;
uint32_t publicKey;
uint32_t sharedKey;

bool claveIntercambiada = false;
unsigned long ultimoEnvio = 0;

/**
 * @brief Envía datos cifrados al servidor a través de UDP
 * 
 * @param claveCifrada Clave cifrada para la comunicación
 * @param mensajeCifrado Mensaje cifrado a enviar
 * @param tag Etiqueta de autenticación
 */
void enviarDatosCifrados(const String& claveCifrada, const String& mensajeCifrado, const String& tag);

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
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a WiFi");

  udp.begin(1235);

  // Generar clave privada y pública.
  //Al implementar cifrado cambiarlo.
  privateKey = random(2, 10);
  publicKey = modexp(g, privateKey, p);

  Serial.print("Clave privada (cliente): ");
  Serial.println(privateKey);
  Serial.print("Clave pública (cliente): ");
  Serial.println(publicKey);

  // Enviar clave pública al servidor
  udp.beginPacket(direccionIP, puerto);
  udp.print(publicKey);
  udp.endPacket();
}

void loop() {
  if (!claveIntercambiada) {
    // Fase de intercambio de claves
    char respuesta[255];
    int tamano = udp.parsePacket();

    if (tamano) {
      // Recepción de la clave pública del servidor   
      int len = udp.read(respuesta, 255);
      if (len > 0) {
        respuesta[len] = 0;
      }

      uint32_t serverPublicKey = atoi(respuesta);
      Serial.print("Clave pública recibida del servidor: ");
      Serial.println(serverPublicKey);

      // Cálculo de la clave compartida
      sharedKey = (uint32_t)pow(serverPublicKey, privateKey) % p;
      Serial.print("Clave secreta compartida: ");
      Serial.println(sharedKey);
      claveIntercambiada = true;
    }
  }else {
    // Fase de envío periódico de datos cifrados
    // Enviar datos cifrados cada 3 segundos (se puede cambiar)
    if (millis() - ultimoEnvio > 3000) {
      String claveCifrada = "ESTA_SERIA_LA_CLAVE";  
      String mensajeCifrado = "ESTO_SERIA_EL_MENSAJE";  
      String tag = "ESTO_SERIA_EL_TAG";              

      enviarDatosCifrados(claveCifrada, mensajeCifrado, tag);
      ultimoEnvio = millis();
    }
  }
}

void enviarDatosCifrados(const String& claveCifrada, const String& mensajeCifrado, const String& tag) {
  // Formatea el paquete separando los campos con ; 
  String paquete = claveCifrada + ";" + mensajeCifrado + ";" + tag;

  // Envía el paquete UDP
  udp.beginPacket(direccionIP, puerto);
  udp.print(paquete);
  udp.endPacket();

  Serial.println("Datos enviados:");
  Serial.println(paquete);
}
