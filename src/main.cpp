
/**
 * @file main.cpp
 * @brief Main entry point for the OpenSailingRC-Anemometer-v2 project.
 *
 * This file initializes the M5Stack Atom S3 device and sets up the Logger instance.
 * The setup() function configures the display and logs a welcome message.
 * The loop() function is currently empty and can be used for main application logic.
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
 * @brief Arduino setup function
 *
 * This function runs once at startup. It initializes the M5Stack Atom S3,
 * configures the display, and logs a welcome message to all enabled outputs.
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
 * @brief Arduino loop function
 *
 * This function runs repeatedly after setup(). Place main application logic here.
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
  data.anemometerId = 1; // Set your anemometer ID here
  WiFi.macAddress(data.macAddress);
  data.windSpeed = windSpeed;

  // Broadcast the data
  comm.broadcast(data);

  // Delay for 2 seconds before the next reading
  delay(2000); 

}
