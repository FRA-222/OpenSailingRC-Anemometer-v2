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
 * @brief Enable or disable screen logging
 * 
 * This method allows runtime control of screen logging functionality.
 * When enabled, log messages will be displayed on the M5Stack screen.
 * When disabled, screen output will be suppressed.
 * 
 * @param enable True to enable screen logging, false to disable
 */
#include "Logger.h"

/**
 * @brief Logger constructor
 * Initializes logging channels and screen if enabled.
 */
Logger::Logger(bool enableSDLogging, bool serialLogging, bool screenLogging) {
    this->sdLogging = enableSDLogging;
    this->serialLogging = serialLogging;
    this->screenLogging = screenLogging;
    this->screenLine = 0;

    // Initialize screen if screen logging is enabled
    if (this->screenLogging) {
        M5.Display.fillScreen(WHITE);
        M5.Display.setTextColor(BLACK);
        M5.Display.setTextSize(2);
        M5.Display.setCursor(0, 0);
    }

    // Initialize serial if serial logging is enabled
    if (this->serialLogging) {
        Serial.begin(115200);
        while (!Serial); // Wait for Serial to be ready
    }

    // TODO: Initialize SD card if SD logging is enabled
    if (this->sdLogging) {
        // SD card initialization code here
    }
}

/**
 * @brief Log a message to enabled outputs (serial, screen, SD card)
 * @param message The message to log
 */
void Logger::log(const String& message) {
    // Serial logging
    if (serialLogging) {
        Serial.println(message);
    }

    // Screen logging
    if (screenLogging) {
        if (screenLine >= MAX_LINES) {
            M5.Display.fillScreen(WHITE);
            screenLine = 0;
        }
        M5.Display.setCursor(0, screenLine * LINE_HEIGHT);
        M5.Display.println(message);
        screenLine++;
    }

    // SD logging
    if (sdLogging) {
        // TODO: Implement SD card logging
        // File file = SD.open("/log.txt", FILE_APPEND);
        // if (file) {
        //     file.println(message);
        //     file.close();
        // }
    }
}

/**
 * @brief Enable or disable SD card logging
 * @param enable True to enable, false to disable
 */
void Logger::enableSDLogging(bool enable) {
    sdLogging = enable;
}

/**
 * @brief Enable or disable serial logging
 * @param enable True to enable, false to disable
 */
void Logger::enableSerialLogging(bool enable) {
    serialLogging = enable;
}


/**
 * @brief Enables or disables screen logging functionality.
 * 
 * This method controls whether log messages are displayed on the screen/display.
 * When enabled, log messages will be output to the connected screen device.
 * When disabled, screen logging is turned off to potentially save resources
 * or reduce visual clutter.
 * 
 * @param enable True to enable screen logging, false to disable it
 */
void Logger::enableScreenLogging(bool enable) {
    screenLogging = enable;
}
