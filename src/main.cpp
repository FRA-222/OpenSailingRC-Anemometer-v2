

// Copyright (C) 2025 Philippe Hubert
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

/**
 * @file main.cpp
 * @brief Main entry point for the OpenSailingRC-Anemometer-v2 project.
 * 
 * This application runs on an M5Stack Atom S3 device and implements a wind speed
 * anemometer with wireless communication capabilities. The system continuously
 * measures wind speed, displays it on the device screen, logs the data, and
 * broadcasts the measurements over WiFi.
 * 
 * Key Features:
 * - Real-time wind speed measurement using Anemometer class
 * - Visual display of wind speed on M5Stack Atom S3 screen
 * - Configurable logging to Serial, SD card, and/or screen
 * - Wireless data broadcasting with unique device identification
 * - 2-second update interval for measurements
 * 
 * The main loop performs the following operations:
 * 1. Updates anemometer readings
 * 2. Retrieves current wind speed
 * 3. Logs the measurement
 * 4. Updates the display
 * 5. Broadcasts data via WiFi
 * 6. Waits 2 seconds before next iteration
 * 
 * Hardware Requirements:
 * - M5Stack Atom S3 device
 * - Compatible anemometer sensor
 * - WiFi connectivity
 * 
 * @author Philippe Hubert
 * @date 2025
 * @license GPL v3.0 or later
 */

#include <M5Unified.h>
#include "Logger.h"
#include "Anemometer.h"
#include "Communication.h"


// Create a Logger instance (enable SD logging if needed)
Logger logger(false, true, false); // SD logging disabled, Serial logging enabled, Screen logging disabled

// Create an Anemometer instance
Anemometer anemometer;

// Create a Communication instance
Communication comm;


/**
 * @brief Setup function for the M5Stack Atom S3 anemometer application
 * 
 * This function initializes the M5Stack Atom S3 device, configures the display,
 * sets up logging, and initializes both the Anemometer and Communication modules.
 * It is called once at the start of the program.
 */
void setup() {
  // M5Stack Atom S3 initialization
  auto cfg = M5.config();
  M5.begin(cfg);

  // Set the screen to white and the text color to black
  M5.Display.fillScreen(WHITE);
  M5.Display.setTextColor(BLACK);
  M5.Display.setTextSize(2);

  // Log a welcome message
  logger.log("Setup started");

  // Set loggers for both classes
  Anemometer::setLogger(logger);
  Communication::setLogger(logger);

  // Anemometer and Communication setup
  anemometer.setup();
  comm.setup();

  logger.log("Setup complete");
}

/**
 * @brief Display wind speed on the Atom S3 screen
 * 
 * This function displays the wind speed value in large text with "m/s" unit below.
 * It clears the previous value before displaying the new one.
 * 
 * @param windSpeed The wind speed value to display in m/s
 */
void displayWindSpeed(float windSpeed) {
  // Clear the screen
  M5.Display.fillScreen(WHITE);
  
  // Set large text size for wind speed value
  M5.Display.setTextSize(3);
  M5.Display.setTextColor(BLACK);
  
  // Convert wind speed to string with 1 decimal place
  String speedStr = String(windSpeed, 1);
  
  // Calculate text width to center it
  int16_t textWidth = M5.Display.textWidth(speedStr);
  int16_t x = (M5.Display.width() - textWidth) / 2;
  int16_t y = M5.Display.height() / 2 - 20;
  
  // Display wind speed value
  M5.Display.setCursor(x, y);
  M5.Display.print(speedStr);
  
  // Set smaller text size for unit
  M5.Display.setTextSize(2);
  String unitStr = "m/s";
  int16_t unitWidth = M5.Display.textWidth(unitStr);
  int16_t unitX = (M5.Display.width() - unitWidth) / 2;
  int16_t unitY = y + 35;
  
  // Display unit
  M5.Display.setCursor(unitX, unitY);
  M5.Display.print(unitStr);
}

/**
 * @brief Main application loop for wind speed monitoring and data broadcasting
 * 
 * This function executes continuously after the initial setup is complete. It performs
 * the core functionality of the anemometer system in a cyclical manner with a 2-second
 * interval between iterations.
 * 
 * The loop performs the following sequence of operations:
 * 1. Updates the anemometer sensor readings to get fresh wind speed data
 * 2. Retrieves the current wind speed measurement in m/s
 * 3. Logs the wind speed value with 2 decimal precision to configured outputs
 * 4. Updates the M5Stack Atom S3 display with the current wind speed reading
 * 5. Prepares an AnemometerData structure containing:
 *    - Message type identifier (2 for anemometer)
 *    - Unique anemometer ID (currently set to 1)
 *    - Device MAC address for identification
 *    - Current wind speed measurement
 * 6. Broadcasts the data packet via WiFi to connected clients
 * 7. Waits 2 seconds before starting the next measurement cycle
 * 
 * This continuous operation ensures real-time monitoring and transmission of wind
 * speed data while maintaining a consistent update rate suitable for most sailing
 * and weather monitoring applications.
 * 
 * @note The 2-second delay provides a balance between responsive updates and
 *       system stability while preventing excessive data transmission
 */
void loop() {
  
  // Main code to run repeatedly
  anemometer.update();

  // Get the current wind speed
  float windSpeed = anemometer.getWindSpeed();

  // Log the wind speed
  logger.log("Wind Speed: " + String(windSpeed, 2) + " m/s");

  // Update the display with the current wind speed
  displayWindSpeed(windSpeed);

  // Prepare data for broadcast
  AnemometerData data;
  data.messageType = 2; // 2 = Anemometer
  
  // Get MAC address and format as string
  WiFi.macAddress(data.macAddress);
  String macString = "";
  for (int i = 0; i < 6; i++) {
    if (data.macAddress[i] < 16) macString += "0";
    macString += String(data.macAddress[i], HEX);
    if (i < 5) macString += ":";
  }
  macString.toUpperCase();
  strcpy(data.anemometerId, macString.c_str());
  
  data.windSpeed = windSpeed;

  // Broadcast the data
  comm.broadcast(data);

  // Delay for 2 seconds before the next reading
  delay(2000); 

}
