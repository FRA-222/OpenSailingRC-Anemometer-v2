// Copyright (C) 2025 Philippe Hubert
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

/**
 * @file Communication.cpp
 * @brief Implementation of the Communication class for ESP-NOW wireless communication
 * @author Philippe Hubert
 * @date 2025
 * @copyright GNU General Public License v3.0 or later
 * 
 * This file contains the implementation of the Communication class which handles
 * wireless communication using ESP-NOW protocol for broadcasting anemometer data.
 * The class provides functionality to initialize ESP-NOW, configure WiFi in station
 * mode, and broadcast anemometer data to all peers using a broadcast MAC address.
 * 
 * Key features:
 * - ESP-NOW initialization and configuration
 * - WiFi station mode setup
 * - Broadcast communication to all peers
 * - Integrated logging support
 * - Error handling for communication failures
 * 
 * Dependencies:
 * - ESP-NOW library for wireless communication
 * - WiFi library for network configuration
 * - Custom Logger class for debugging and monitoring
 * - AnemometerData structure for data transmission
 */

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

/**
 * @brief Setup Communication
 * Initializes ESPNow and configures WiFi in station mode.
 */
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
