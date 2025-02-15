
#include "Model/GeneratorForEsp32.hpp"

#ifdef ESP32

#include "AD9833.h"
#include "ModuleConfig.hpp"

GeneratorForEsp32::GeneratorForEsp32(const uint8_t spiCsLine)
    : m_spi(nullptr)
{
    m_AD = new AD9833(spiCsLine, CHANNEL_1_SPI_SDATA, CHANNEL_1_SPI_SCLK);
    if (m_AD != nullptr)
    {
        m_AD->begin();
    }
}

#endif
