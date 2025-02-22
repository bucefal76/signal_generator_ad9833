
#include "Model/GeneratorForEsp32.hpp"

#ifdef ESP32

#include "AD9833.h"
#include "ModuleConfig.hpp"

GeneratorForEsp32::GeneratorForEsp32(const uint8_t generatorId, const uint8_t spiCsLine, const uint8_t spiDataLine, const uint8_t spiClockLine)
    : GeneratorAd9833(generatorId)
{
    m_AD = new AD9833(spiCsLine, spiDataLine, spiClockLine);
    if (m_AD != nullptr)
    {
        m_AD->begin();

        connectivityTest();
    }
}

GeneratorForEsp32::GeneratorForEsp32(const uint8_t generatorId, SPIClass *spi, const uint8_t spiCsLine)
    : GeneratorAd9833(generatorId)
{
    m_AD = new AD9833(spiCsLine, spi);

    if (m_AD != nullptr)
    {
        m_AD->begin();

        connectivityTest();
    }
}

#endif
