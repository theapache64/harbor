#include <ESP8266WiFi.h>
#include <Keys.cpp>

class WiFiConnection {

public:
    void connectToWifi() {
        WiFi.mode(WIFI_STA);
        WiFi.begin(SSID, PASSWORD);
        Serial.print("Connecting to WiFi ...");
        while (WiFi.status() != WL_CONNECTED) {
            Serial.print('.');
            delay(1000);
        }
        Serial.println();
    }

    bool isConnected(){
        return WiFi.status() == WL_CONNECTED;
    }
};