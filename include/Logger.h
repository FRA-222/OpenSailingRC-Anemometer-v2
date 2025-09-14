
#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include <M5Unified.h>

/**
 * @brief Logger class for serial, screen, and SD card logging.
 *
 * This class provides logging functionalities for serial output, screen display (AtomS3),
 * and SD card file logging. Logging channels can be enabled or disabled independently.
 */
class Logger {
private:
    bool sdLogging;        // Enable/disable SD card logging
    bool serialLogging;    // Enable/disable serial logging
    bool screenLogging;    // Enable/disable screen logging
    int screenLine;        // Current line on the screen
    static const int MAX_LINES = 8;    // Maximum lines for AtomS3 screen
    static const int LINE_HEIGHT = 16; // Height of each line on screen

public:
    /**
     * @brief Construct a new Logger object
     * @param enableSDLogging Enable SD card logging
     * @param enableSerialLogging Enable serial logging
     * @param enableScreenLogging Enable screen logging
     */
    Logger(bool enableSDLogging = false, bool enableSerialLogging = true, bool enableScreenLogging = true);

    /**
     * @brief Log a message to enabled outputs
     * @param message The message to log
     */
    void log(const String& message);

    /**
     * @brief Enable or disable serial logging
     * @param enable True to enable, false to disable
     */
    void enableSerialLogging(bool enable);

    /**
     * @brief Enable or disable screen logging
     * @param enable True to enable, false to disable
     */
    void enableScreenLogging(bool enable);

    /**
     * @brief Enable or disable SD card logging
     * @param enable True to enable, false to disable
     */
    void enableSDLogging(bool enable);
};

#endif // LOGGER_H
