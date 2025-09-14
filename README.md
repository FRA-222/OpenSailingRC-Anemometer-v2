# OpenSailingRC Anemometer v2

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Platform](https://img.shields.io/badge/Platform-ESP32--S3-orange.svg)](https://www.espressif.com/en/products/socs/esp32-s3)
[![Hardware](https://img.shields.io/badge/Hardware-M5Stack%20Atom%20S3-red.svg)](https://shop.m5stack.com/products/atoms3-dev-kit-w-0-85-inch-screen)

An intelligent anemometer based on M5Stack Atom S3 for wireless wind speed measurement and transmission, designed for radio-controlled sailing applications.

## 🌟 Features

- **Real-time measurement**: Continuous wind speed readings
- **Visual display**: User interface on M5Stack Atom S3 screen
- **Wireless communication**: Data transmission via ESP-NOW
- **Advanced logging**: Recording to serial port, SD card, and screen
- **Modular architecture**: Code organized in reusable classes
- **Unique identification**: Each device has a unique network ID

## 🛠 Hardware Requirements

- **M5Stack Atom S3** - Main microcontroller
- **M5Stack Voltmeter Unit** - Measurement interface (ADS1115)
- **Analog Anemometer** - Wind speed sensor
- **MicroSD Card** (optional) - For data logging

## 📋 Technical Specifications

- **Processor**: ESP32-S3 (dual-core, 240MHz)
- **Connectivity**: WiFi 802.11 b/g/n, ESP-NOW
- **ADC Resolution**: 16-bit (ADS1115)
- **Measurement Range**: 0-100+ m/s (configurable)
- **Sample Rate**: 0.5 Hz (2 seconds)
- **Voltage Accuracy**: ±0.1% with calibration

## 🏗 Code Architecture

### Main Classes

#### `Anemometer`
Manages wind speed measurement reading and conversion
- ADS1115 ADC interfacing
- Calibration and voltage → speed conversion
- Measurement filtering and smoothing

#### `Communication`
Handles ESP-NOW wireless communication
- WiFi network configuration
- Anemometer data broadcasting
- Transmission error handling

#### `Logger`
Multi-channel logging system
- Serial output for debugging
- LCD screen display
- SD card recording

### Data Structure

```cpp
typedef struct {
    uint32_t anemometerId;   // Unique anemometer ID
    uint8_t macAddress[6];   // Device MAC address
    float windSpeed;         // Wind speed (m/s)
} AnemometerData;
```

## ⚙️ Installation

### Prerequisites

1. **PlatformIO** installed in VS Code
2. **USB drivers** for M5Stack Atom S3
3. **Git** to clone the repository

### Installation Steps

```bash
# Clone the repository
git clone https://github.com/FRA-222/OpenSailingRC-Anemometer-v2.git
cd OpenSailingRC-Anemometer-v2

# Open with PlatformIO
code .

# Build and upload
pio run -t upload
```

### Dependencies

The following libraries are automatically installed via PlatformIO:

```ini
lib_deps = 
    m5stack/M5Unified@^0.1.14
    wnatth3/WiFiManager@^2.0.16-rc.2
    fastled/FastLED@^3.9.0
    m5stack/M5AtomS3@^1.0.2
    m5stack/M5-ADS1115@^1.0.0
```

## 🔧 Configuration

### Anemometer Calibration

Calibration is done via arrays in `Anemometer.cpp`:

```cpp
// Calibration curve: Voltage (mV) → Speed (m/s)
static float INPUT_WIND_SPEED_VS_VOLTAGE[] = {
    2000., 3000., 3500., 3659., 3765., 3800., 
    3829., 3851., 3875., 3900., 3930., 3988., 
    4090., 4200., 4500.
};

static float OUTPUT_WIND_SPEED_VS_VOLTAGE[] = {
    0., 0., 5., 10., 20., 30., 
    40., 50., 60., 70., 80., 90., 
    97., 100., 100.
};
```

### Logger Configuration

In `main.cpp`, adjust logger parameters:

```cpp
// Logger(SD, Serial, Screen)
Logger logger(false, true, true);
```

### Anemometer ID

Modify the unique ID in the main loop:

```cpp
data.anemometerId = 1; // Change this value for each device
```

## 📊 Usage

### Startup

1. Power on the M5Stack Atom S3
2. The system initializes automatically
3. The screen displays "Init" then "Après setup"
4. Measurements begin immediately

### User Interface

- **Main screen**: Wind speed display in m/s
- **Serial port**: Debug messages and detailed values
- **LED**: System status indicator

### Transmitted Data

Data is broadcast via ESP-NOW every 2 seconds:
- Anemometer ID
- Device MAC address
- Current wind speed

## 🔍 Debugging

### Serial Messages

```
Init
Après setup
Wind Speed: 5.42 m/s
ESP-NOW broadcast success
```

### Error Codes

- `Unit Vmeter Init Fail`: ADC initialization problem
- `Error initializing ESP-NOW`: WiFi communication error
- `ESP-NOW broadcast failed`: Transmission failure

## 🤝 Contributing

Contributions are welcome! Please:

1. Fork the project
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Open a Pull Request

### Code Standards

- Comments in French (legacy code)
- Document public functions
- Unit tests for new features
- Follow existing naming conventions

## 📝 License

This project is licensed under the **GNU General Public License v3.0**. See the [LICENSE](LICENSE.md) file for details.

```
Copyright (C) 2025 Philippe Hubert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
```

## 👤 Author

**Philippe Hubert** - *Initial development* - [FRA-222](https://github.com/FRA-222)

## 🙏 Acknowledgments

- **M5Stack** for the hardware ecosystem
- **Espressif** for the ESP32-S3 processor
- **PlatformIO Community** for the development environment
- **OpenSailingRC Community** for testing and feedback

## 📚 Additional Documentation

- [Project Wiki](../../wiki)
- [Calibration Guide](docs/calibration.md)
- [API Reference](docs/api.md)
- [Troubleshooting](docs/troubleshooting.md)

## 🔗 Useful Links

- [M5Stack Website](https://m5stack.com/)
- [ESP32-S3 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/)
- [PlatformIO Documentation](https://docs.platformio.org/)
- [ESP-NOW Protocol](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_now.html)

---

*This project is part of the OpenSailingRC ecosystem for radio-controlled sailing.*