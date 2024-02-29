#ifndef Config_h
#define Config_h

#include <Arduino.h>
#include <EEPROM.h>
#include <ArduinoJson.h>

class ConfigManager {
public:
    struct Login {
        String username;
        String password;
    };

    struct Wifi {
        String ssid;
        String password;
    };

    struct Ap {
        String ssid;
        String password;
    };

    struct Mqtt {
        bool enabled;
        String broker;
        int port;
        String user;
        String password;
        String topic;
    };

    ConfigManager();
    void begin(int eepromSize = 1024);
    int load();
    bool save();
    void setDebugMode(bool mode);
    String GetJson();
    void SetJson(const String& json);

    Login login;
    Wifi wifi;
    Ap ap;
    Mqtt mqtt;

private:
    int _eepromSize;
    bool _debugMode;
    String _jsonStr;
};

#endif
