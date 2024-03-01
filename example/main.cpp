#include <Arduino.h>
#include "ConfigManager.h"

// lib_deps =
//    https://github.com/GilbertoBojorquezDelgado/ObjetoIoT_ManagerConfig

// Borrar la memoria EEPROM -> pio run -t erase

ConfigManager config;

void setup() {
    Serial.begin(9600);
    while (!Serial);

    // Inicializa la EEPROM con el tamaño configurado
    config.begin(); // Por Default 1024 -- Ejemplo de otro valor, config.begin(512);

    // Recuperando datos desde la EEPROM
    if (config.load() == 1) {
        Serial.println("Datos cargados desde EEPROM.");
    } else {
        Serial.println("No se encontraron datos en EEPROM.");
    }

    // Mostrando en JSON las configuraciones
    Serial.print("Configuraciones actuales en JSON: ");
    Serial.println(config.GetJson());

    // Mostrar por campo las configuraciones
    Serial.print("config.mqtt.broker: ");
    Serial.println(config.mqtt.broker);

    // Almacenando datos de por segmento.
    //config.mqtt.topic = "test";
    //config.save();

    // Almacenando Datos por Bloque (JSON)
    //String newJson = R"({
    //    "LOGIN": {"username": "nuevoUsuario", "password": "nuevaContraseña"},
    //    "WIFI": {"ssid": "nuevoSSID", "password": "nuevoPassword"},
    //     "AP": {"ssid": "nuevoAPSSID", "password": "nuevoAPPassword"},
    //     "MQTT": {"enabled": true, "broker": "nuevoBroker", "port": 1883, "user": "nuevoUser", "password": "nuevoMQTTPassword", "topic": "nuevoTopic"}
    // })";
    //config.SetJson(newJson);
    //config.save();

}

void loop()
{
    // Aquí puedes implementar la lógica principal de tu programa
}
