
#include "Model/GeneratorForEsp32.hpp"

#ifdef ESP32

#include "AD9833.h"
#include "ModuleConfig.hpp"

GeneratorForEsp32::GeneratorForEsp32(const uint8_t spiCsLine, const uint8_t spiDataLine, const uint8_t spiClockLine)
{
    m_AD = new AD9833(spiCsLine, spiDataLine, spiClockLine);
    if (m_AD != nullptr)
    {
        m_AD->begin();
    }
}

#endif
