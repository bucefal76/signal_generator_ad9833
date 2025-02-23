#ifndef MODULECONFIG_HPP
#define MODULECONFIG_HPP

/// @brief Configuration of the module

// To use two AD9833 chips for two channels, set this define.
// If you do not set it, one AD9833 will be utilized for generator channel 1
// and the wobbulator.
// When defined, two AD9833 chips will be used: one for generator channel 1
// and the wobbulator, and the other for generator channel 2.
/* #define USE_TWO_GENERATORS_FOR_TWO_CHANNELS */

#define WOBBULATOR_NUMBER_OF_STEPS 50

// Select your CPU, ESP32 in Wemos D1 R32  or Atmel ATmega in UNO
#ifdef USE_ESP32
#define ESP_WATCHDOG_TIMEOUT_SEK 3U

#define ESP32_CHANNEL_1_SPI_CS 12
#define ESP32_CHANNEL_1_SPI_SCLK 18
#define ESP32_CHANNEL_1_SPI_SDATA 23

#define ESP32_CHANNEL_2_SPI_CS 13
#define ESP32_CHANNEL_2_SPI_SCLK ESP32_CHANNEL_1_SPI_SCLK
#define ESP32_CHANNEL_2_SPI_SDATA ESP32_CHANNEL_1_SPI_SDATA

// DAC resolution is 8 bits, so 256 steps
#define WOBBULATOR_RAMP_SIGNAL_STEP (256 / WOBBULATOR_NUMBER_OF_STEPS)

/* #define ESP32_USE_HARDWARE_SPI */
// I think there is a bug in the AD9833 library at ESP32
// I could not make it work with two generators because problem with select line.
#else

// DAC resolution is 12 bits, so 4095 steps
#define WOBBULATOR_RAMP_SIGNAL_STEP (4095 / WOBBULATOR_NUMBER_OF_STEPS)

// I2C address for external ADC used for wobbulator ramp signal
// Note usually it is 0x62U, my ADC was set to 0x60U, check your I2C address.
#define WOBBULATOR_RAMP_SIGNAL_ADC_I2C_ADDRESS 0x60U

#define UNO_CHANNEL_1_SPI_CS 10
#define UNO_CHANNEL_2_SPI_CS 9
#endif

#define VOBULATOR_THREAD_TIME_INTERVAL_MS 250U

// Use serial port for user menu and debug print, this is default.
#define USE_SERIAL
#ifdef USE_SERIAL
#define SERIAL_MENU_THREAD_TIME_INTERVAL_MS 100U
#endif

//
#define USE_X9C103S_POTENTIOMETER_TO_NORMALIZE_WAVEFORMS_AMPLITUDES
#ifdef USE_X9C103S_POTENTIOMETER_TO_NORMALIZE_WAVEFORMS_AMPLITUDES

#ifdef USE_ESP32
#define X9C103S_POTENTIOMETER_CHANNEL_1_CS_PIN 16
#ifdef USE_TWO_GENERATORS_FOR_TWO_CHANNELS
#define X9C103S_POTENTIOMETER_CHANNEL_2_CS_PIN 17
#endif
#define X9C103S_POTENTIOMETER_INC_PIN 27
#define X9C103S_POTENTIOMETER_UD_PIN 14
#else
#define X9C103S_POTENTIOMETER_CHANNEL_1_CS_PIN 6
#ifdef USE_TWO_GENERATORS_FOR_TWO_CHANNELS
#define X9C103S_POTENTIOMETER_CHANNEL_2_CS_PIN 5
#endif
#define X9C103S_POTENTIOMETER_INC_PIN 8
#define X9C103S_POTENTIOMETER_UD_PIN 7
#endif

#endif

#endif