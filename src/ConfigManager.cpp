#include "ConfigManager.h"

ConfigManager::ConfigManager() : _eepromSize(1024), _debugMode(false) {}

void ConfigManager::begin(int eepromSize) {
    _eepromSize = eepromSize;
    EEPROM.begin(_eepromSize);
}

int ConfigManager::load() {
    String jsonStr;
    bool datosEncontrados = false;

    for (int i = 0; i < _eepromSize; i++) {
        char ch = EEPROM.read(i);
        if (ch == '\0') break;
        jsonStr += ch;
    }

    if (jsonStr.length() > 0 && jsonStr[0] != '\xFF') {
        DynamicJsonDocument doc(_eepromSize);
        DeserializationError error = deserializeJson(doc, jsonStr);

        if (!error) {
            login.username = doc["LOGIN"]["username"].as<String>();
            login.password = doc["LOGIN"]["password"].as<String>();
            wifi.ssid = doc["WIFI"]["ssid"].as<String>();
            wifi.password = doc["WIFI"]["password"].as<String>();
            ap.ssid = doc["AP"]["ssid"].as<String>();
            ap.password = doc["AP"]["password"].as<String>();
            mqtt.enabled = doc["MQTT"]["enabled"].as<bool>();
            mqtt.broker = doc["MQTT"]["broker"].as<String>();
            mqtt.port = doc["MQTT"]["port"].as<int>();
            mqtt.user = doc["MQTT"]["user"].as<String>();
            mqtt.password = doc["MQTT"]["password"].as<String>();
            mqtt.topic = doc["MQTT"]["topic"].as<String>();

            _jsonStr = jsonStr; // Guarda la cadena JSON original

            if (_debugMode) {
                Serial.println("JSON recuperado:");
                serializeJsonPretty(doc, Serial);
            }

            datosEncontrados = true;
        } else if (_debugMode) {
            Serial.print("Error al deserializar JSON: ");
            Serial.println(error.c_str());
        }
    }

    return datosEncontrados ? 1 : 0;
}

bool ConfigManager::save() {
    DynamicJsonDocument doc(_eepromSize);

    doc["LOGIN"]["username"] = login.username;
    doc["LOGIN"]["password"] = login.password;
    doc["WIFI"]["ssid"] = wifi.ssid;
    doc["WIFI"]["password"] = wifi.password;
    doc["AP"]["ssid"] = ap.ssid;
    doc["AP"]["password"] = ap.password;
    doc["MQTT"]["enabled"] = mqtt.enabled;
    doc["MQTT"]["broker"] = mqtt.broker;
    doc["MQTT"]["port"] = mqtt.port;
    doc["MQTT"]["user"] = mqtt.user;
    doc["MQTT"]["password"] = mqtt.password;
    doc["MQTT"]["topic"] = mqtt.topic;

    String jsonStr;
    serializeJson(doc, jsonStr);

    if (jsonStr.length() > _eepromSize) {
        if (_debugMode) {
            Serial.println("Error: Los datos de configuración exceden el tamaño de la EEPROM.");
        }
        return false;
    }

    for (int i = 0; i < jsonStr.length(); i++) {
        EEPROM.write(i, jsonStr[i]);
    }
    EEPROM.write(jsonStr.length(), '\0');

    if (!EEPROM.commit()) {
        if (_debugMode) {
            Serial.println("Error al guardar en la EEPROM");
        }
        return false;
    }

    if (_debugMode) {
        Serial.println("Configuracion guardada exitosamente.");
    }
    return true;
}

void ConfigManager::setDebugMode(bool mode) {
    _debugMode = mode;
}

String ConfigManager::GetJson() {
    return _jsonStr;
}

void ConfigManager::SetJson(const String& json) {
    DynamicJsonDocument doc(_eepromSize);
    DeserializationError error = deserializeJson(doc, json);

    if (!error) {
        login.username = doc["LOGIN"]["username"].as<String>();
        login.password = doc["LOGIN"]["password"].as<String>();
        wifi.ssid = doc["WIFI"]["ssid"].as<String>();
        wifi.password = doc["WIFI"]["password"].as<String>();
        ap.ssid = doc["AP"]["ssid"].as<String>();
        ap.password = doc["AP"]["password"].as<String>();
        mqtt.enabled = doc["MQTT"]["enabled"].as<bool>();
        mqtt.broker = doc["MQTT"]["broker"].as<String>();
        mqtt.port = doc["MQTT"]["port"].as<int>();
        mqtt.user = doc["MQTT"]["user"].as<String>();
        mqtt.password = doc["MQTT"]["password"].as<String>();
        mqtt.topic = doc["MQTT"]["topic"].as<String>();

        _jsonStr = json; // Actualiza con la nueva cadena JSON

        if (_debugMode) {
            Serial.println("Configuración actualizada desde JSON.");
        }
    } else if (_debugMode) {
        Serial.print("Error al deserializar JSON: ");
        Serial.println(error.c_str());
    }
}
