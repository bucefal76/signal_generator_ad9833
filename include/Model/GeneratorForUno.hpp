#ifndef GENRATORFORUNO_HPP
#define GENRATORFORUNO_HPP

#include "Model/GeneratorAd9833.hpp"

#ifndef USE_ESP32

/// @brief Class to generate waves with the AD9833 function generator
/// for the Arduino Uno board.
class GeneratorForUno : public GeneratorAd9833
{

public:
    /// @brief Constructor to initialize the generator.
    /// The implementation is specific to the Arduino Uno board.
    /// All other functionality is same as the GeneratorAd9833 class.
    /// At default it always uses a hardware SPI interface, lines 10,11,13.
    /// @param generatorId The generator ID used by f.e. menu display.
    /// @param spiCsLine The chip select line to use (e.g. 10).
    GeneratorForUno(const uint8_t generatorId, uint8_t spiCsLine);
};

#endif

#endif