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
 * @file Anemometer.cpp
 * @brief Implementation of the Anemometer class for wind speed measurement
 * @author Philippe Hubert
 * @date 2025
 * @copyright GNU General Public License v3.0
 * 
 * This file implements an anemometer system that measures wind speed by converting
 * voltage readings from an M5Stack Unit VMeter to wind speed values using a
 * predefined calibration curve.
 * 
 * The system uses:
 * - M5Stack Unit VMeter (I2C address 0x49) for voltage measurement
 * - ADS1115 ADC with configurable gain and sampling rate
 * - Linear interpolation between calibration points for voltage-to-wind-speed conversion
 * 
 * Key features:
 * - Automatic initialization and configuration of the VMeter unit
 * - Real-time voltage and wind speed measurement
 * - Calibration correction factor application
 * - Logging support for debugging and monitoring
 * - Simulation mode for testing (sinusoidal voltage generation)
 * 
 * Hardware configuration:
 * - I2C communication on Wire1 (pins 2, 1)
 * - 400kHz I2C frequency
 * - ADS1115 PGA gain set to 2048 (max 32V input)
 * - Single-shot conversion mode at 8 SPS rate
 * 
 * Calibration:
 * - Input voltage range: 0-14V
 * - Output wind speed range: 0-28 m/s
 * - Linear interpolation between calibration points
 * - Factory calibration factor from EEPROM
 * - Additional correction coefficient: 1.0051
 */


#include "Anemometer.h"

// Static member initialization
Logger* Anemometer::logger_ = nullptr;

// VMeter Management
#define M5_UNIT_VMETER_I2C_ADDR             0x49
#define M5_UNIT_VMETER_EEPROM_I2C_ADDR      0x53
#define M5_UNIT_VMETER_PRESSURE_COEFFICIENT 0.015918958F

// Courbe de capacite d un element / Tension (attention !!!!! abscisses identiques interdites)
static float INPUT_WIND_SPEED_VS_VOLTAGE[]={0.,1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.,13.,14.}; 
static float OUTPUT_WIND_SPEED_VS_VOLTAGE[]={0.,2.,4.,6.,8.,10.,12.,14.,16.,18.,20.,22.,24.,26.,28.}; 


/**
 * @brief Construct a new Anemometer object
 */
Anemometer::Anemometer() : voltmeter_(), voltage_(0.0f), windSpeed_(0.0f) {}

/**
 * @brief Set the logger instance for the class
 */
void Anemometer::setLogger(Logger& logger) {
    logger_ = &logger;
}

/**
 * @brief Log a message using the class logger
 */
void Anemometer::log(const String& message) {
    if (logger_) {
        logger_->log(message);
    }
}

/**
 * @brief Initialize the anemometer
 */
void Anemometer::setup() {

    // Additional setup code can be added here
    while (!voltmeter_.begin(&Wire1, M5_UNIT_VMETER_I2C_ADDR, 2, 1, 400000U)) {
        logger_->log("Unit Vmeter Init Fail");
        delay(1000);
    }
    //logger_->log("# Unit Vmeter OK");
    voltmeter_.setEEPROMAddr(M5_UNIT_VMETER_EEPROM_I2C_ADDR);
    voltmeter_.setMode(ADS1115_MODE_SINGLESHOT);
    voltmeter_.setRate(ADS1115_RATE_8);
    voltmeter_.setGain(ADS1115_PGA_2048);
    // | PGA      | Max Input Voltage(V) |
    // | PGA_6144 |        128           |
    // | PGA_4096 |        64            |
    // | PGA_2048 |        32            |
    // | PGA_512  |        16            |
    // | PGA_256  |        8             |

    resolution_ = voltmeter_.getCoefficient() / M5_UNIT_VMETER_PRESSURE_COEFFICIENT;
    calibration_factor_ = voltmeter_.getFactoryCalibration();
}


/**
 * @brief Update the voltage and wind speed readings
 */
void Anemometer::update() {
    // Read voltage from the voltmeter and convert to wind speed
    // Correction a appliquer / mesures
    float coefCorrection = 1.0051;
    
    int16_t adc_raw = voltmeter_.getSingleConversion();

    float voltage   = adc_raw * resolution_ * calibration_factor_ * coefCorrection;

    // Simulate a random voltage between 0V and 15V for testing
    voltage = 1.5f + 1.5f * sin(millis() / 10000.0f); // Sinusoidal voltage between 0V and 3V with slow evolution

    voltage_ = voltage;
    windSpeed_ = voltageToWindSpeed(voltage);

    // Log the readings
    log("Voltage: " + String(voltage_, 2) + " V, Wind Speed: " + String(windSpeed_, 2) + " m/s");
}

/**
 * @brief Get the last measured voltage
 * @return Voltage in volts
 */
float Anemometer::getVoltage() const {
    return voltage_;
}

/**
 * @brief Get the last calculated wind speed
 * @return Wind speed in m/s
 */
float Anemometer::getWindSpeed() const {
    return windSpeed_;
}


//Calculer l ordonnee y d une courbe xtab, ytab pour l abscisse x
float calculerY(float xtab[], float ytab[], int taille, float x) {
    float y;
    int i;
    i = 0.;
    while (i < taille-2) {
        if (x<xtab[i+1]) break;
        i++;
    }
    y = ((x-xtab[i])*ytab[i+1] + (xtab[i+1]-x)*ytab[i]) / (xtab[i+1]-xtab[i]);
    return y;
} 


/**
 * @brief Convert voltage to wind speed (m/s)
 * @param voltage Voltage value from voltmeter
 * @return Wind speed in m/s
 * @note This is a placeholder formula. Adjust according to your anemometer's calibration.
 */
float Anemometer::voltageToWindSpeed(float voltage) {
    // Example conversion: windSpeed = voltage * 10.0;
    // Replace with your own calibration!

    float windSpeed = calculerY(INPUT_WIND_SPEED_VS_VOLTAGE, OUTPUT_WIND_SPEED_VS_VOLTAGE, 15, voltage);

    return windSpeed;
}
