#ifndef MODULECONFIG_HPP
#define MODULECONFIG_HPP

/// @brief Configuration of the module

// To use two AD9833 chips for two channels, set this define.
// If you do not set it, one AD9833 will be utilized for generator channel 1
// and the wobbulator.
// When defined, two AD9833 chips will be used: one for generator channel 1
// and the wobbulator, and the other for generator channel 2.
/* #define USE_TWO_GENERATORS */

// Select your CPU, ESP32 in Wemos D1 R32  or Atmel ATmega in UNO
#ifdef USE_ESP32
#define ESP_WATCHDOG_TIMEOUT_SEK 3U

#define ESP32_CHANNEL_1_SPI_CS 12
#define ESP32_CHANNEL_1_SPI_SCLK 18
#define ESP32_CHANNEL_1_SPI_SDATA 23

#define ESP32_CHANNEL_2_SPI_CS 13
#define ESP32_CHANNEL_2_SPI_SCLK ESP32_CHANNEL_1_SPI_SCLK
#define ESP32_CHANNEL_2_SPI_SDATA ESP32_CHANNEL_1_SPI_SDATA

/* #define ESP32_USE_HARDWARE_SPI */
// I think there is a bug in the AD9833 library at ESP32
// I could not make it work with two generators because problem with select line.
#else
#define UNO_CHANNEL_1_SPI_CS 10
#define UNO_CHANNEL_2_SPI_CS 9
#endif

// Use serial port for user menu and debug print, this is default.
#define USE_SERIAL
#ifdef USE_SERIAL
#define SERIAL_MENU_THREAD_TIME_INTERVAL_MS 100U
#endif

#define VOBULATOR_THREAD_TIME_INTERVAL_MS 250U

#endif