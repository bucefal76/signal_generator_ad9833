#ifndef GENRATORFORUNO_HPP
#define GENRATORFORUNO_HPP

#include "Model/GeneratorAd9833.hpp"

#ifndef USE_ESP32

/// @brief Class to generate waves with the AD9833 function generator
/// for the Arduino Uno board.
class GeneratorForUno : public GeneratorAd9833
{

public:
    GeneratorForUno(const uint8_t spiCsLine);
};

#endif

#endif