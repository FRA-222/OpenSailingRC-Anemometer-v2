#ifndef ANEMOMETER_H
#define ANEMOMETER_H

#include <Arduino.h>
#include "M5_ADS1115.h"
#include "Logger.h"

/**
 * @brief Anemometer class for wind speed measurement using M5Stack Voltmeter Unit.
 *
 * This class reads the voltage from the M5Stack Voltmeter Unit and converts it to wind speed.
 */
class Anemometer {
private:
    ADS1115 voltmeter_;          // Voltmeter unit instance
    float voltage_;             // Last measured voltage
    float windSpeed_;           // Last calculated wind speed (m/s)
    static Logger* logger_;     // Pointer to Logger instance for logging (static class member)
    float resolution_    = 0.0;
    float calibration_factor_ = 0.0;
    /**
     * @brief Convert voltage to wind speed (m/s)
     * @param voltage Voltage value from voltmeter
     * @return Wind speed in m/s
     * @note You should adjust the conversion formula according to your anemometer's calibration.
     */
    float voltageToWindSpeed(float voltage);

    /**
     * @brief Get the last measured voltage
     * @return Voltage in volts
     */
    float getVoltage() const;

    /**
     * @brief Log a message using the class logger
     * @param message The message to log
     */
    void log(const String& message);

public:
    /**
     * @brief Construct a new Anemometer object
     */
    Anemometer();

    /**
     * @brief Set the logger instance for the class
     * @param logger Reference to a Logger instance for status messages
     */
    static void setLogger(Logger& logger);

    /**
     * @brief Initialize the anemometer
     */
    void setup();

    /**
     * @brief Update the voltage and wind speed readings
     */
    void update();


    /**
     * @brief Get the last calculated wind speed
     * @return Wind speed in m/s
     */
    float getWindSpeed() const;
};

#endif // ANEMOMETER_H
