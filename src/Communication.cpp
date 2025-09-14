#include "Communication.h"


// Static member initialization
Logger* Communication::logger_ = nullptr;

/**
 * @brief Construct a new Communication object
 * Initializes ESPNow and WiFi in station mode.
 */

Communication::Communication() {
}

/**
 * @brief Set the logger instance for the class
 */
void Communication::setLogger(Logger& logger) {
    logger_ = &logger;
}

/**
 * @brief Log a message using the class logger
 */
void Communication::log(const String& message) {
    if (logger_) {
        logger_->log(message);
    }
}

void Communication::setup() {

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    if (esp_now_init() != ESP_OK) {
        log("Error initializing ESP-NOW");
    }

    if (esp_now_init() != ESP_OK) {
        log("Error initializing ESP-NOW");
    } else {
        log("ESP-NOW initialized");
    }
}

/**
 * @brief Broadcast anemometer data using ESPNow
 * @param data Structure containing anemometer ID, MAC address, and wind speed
 * @return true if broadcast was successful, false otherwise
 */
bool Communication::broadcast(const AnemometerData& data) {
    // Broadcast to all peers (broadcast MAC address)
    uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // Add broadcast peer if not already added
    esp_now_add_peer(&peerInfo);

    // Send the data structure
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t*)&data, sizeof(data));
    if (result == ESP_OK) {
        log("ESP-NOW broadcast success");
    } else {
        log("ESP-NOW broadcast failed");
    }
    return (result == ESP_OK);
}
