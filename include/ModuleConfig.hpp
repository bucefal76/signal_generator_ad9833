#ifndef MODULECONFIG_HPP
#define MODULECONFIG_HPP

/// @brief Configuration of the module

#ifdef USE_ESP32
#define ESP_WATCHDOG_TIMEOUT_SEK 3U
#define VOBULATOR_BY_DC_THREAD_TIME_INTERVAL_MS 50U
#define CHANNEL_1_SPI_CS 12
#define CHANNEL_1_SPI_SCLK 18
#define CHANNEL_1_SPI_SDATA 23
#else
#define CHANNEL_1_SPI_CS 10
#endif

#define USE_SERIAL
#ifdef USE_SERIAL
#define SERIAL_MENU_THREAD_TIME_INTERVAL_MS 100U
#endif

#define VOBULATOR_THREAD_TIME_INTERVAL_MS 10U

#endif