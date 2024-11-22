#include "NetworkClient.h"
#include <Arduino.h> // For Serial functionality

// Constructor implementation
NetworkClient::NetworkClient() {
    Serial.println("Creating NetworkClient...");
    // Initialize the secure HTTP client
    httpClient.reset(new BearSSL::WiFiClientSecure);
    httpClient->setInsecure(); // Disable certificate validation for simplicity (use with caution in production)
}
