#ifndef GENERATOR_FOR_ESP32_HPP
#define GENERATOR_FOR_ESP32_HPP

#ifdef ESP32

#include "Model/GeneratorAd9833.hpp"

class SPIClass;

class GeneratorForEsp32 : public GeneratorAd9833
{
public:
    GeneratorForEsp32(const uint8_t spiCsLine);

private:
    SPIClass *m_spi;
};

#endif

#endif // GENERATOR_FOR_ESP32_HPP