#ifndef GENERATOR_FOR_ESP32_HPP
#define GENERATOR_FOR_ESP32_HPP

#ifdef ESP32

#include "Model/GeneratorAd9833.hpp"

class SPIClass;

/// @brief Class to generate waves with the AD9833 function generator
/// for the ESP32 Wemos D1 R32 board.
class GeneratorForEsp32 : public GeneratorAd9833
{
public:
    /// @brief Constructor to initialize the generator.
    /// The implementation is specific to the Wemos D1 R32 ESP32 board.
    /// All other functionality is same as the GeneratorAd9833 class.
    GeneratorForEsp32(const uint8_t generatorId, const uint8_t spiCsLine, const uint8_t spiData, const uint8_t spiClock);
    /// @brief Constructor to initialize the generator with hardware SPI support.
    /// @param spi Pointer to the SPI class (SPI support for ESP32).
    /// @param spiCsLine The chip select line for the SPI (selection of the generator chip)
    GeneratorForEsp32(const uint8_t generatorId, SPIClass *spi, const uint8_t spiCsLine);
};

#endif

#endif // GENERATOR_FOR_ESP32_HPP