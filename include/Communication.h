#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "Logger.h"

/**
 * @brief Structure containing anemometer data for broadcast
 */
typedef struct {
    int8_t messageType;      // 1 = Boat, 2 = Anemometer
    char anemometerId[18];   // MAC address as string (format: "AA:BB:CC:DD:EE:FF")
    uint8_t macAddress[6];   // MAC address of the device
    float windSpeed;         // Wind speed value
} AnemometerData;

/**
 * @brief Communication class for ESPNow broadcast
 */

class Communication {
private:
    static Logger* logger_; // Static pointer to logger instance

public:
    /**
     * @brief Construct a new Communication object
     */
    Communication();

    /**
     * @brief Set the logger instance for the class
     * @param logger Reference to Logger for internal logging
     */
    static void setLogger(Logger& logger);

    /**
     * @brief Setup Communication
     */
    void setup();

    /**
     * @brief Log a message using the class logger
     * @param message The message to log
     */
    void log(const String& message);

    /**
     * @brief Broadcast anemometer data using ESPNow
     * @param data Structure containing anemometer ID, MAC address, and wind speed
     * @return true if broadcast was successful, false otherwise
     */
    bool broadcast(const AnemometerData& data);
};

#endif // COMMUNICATION_H
