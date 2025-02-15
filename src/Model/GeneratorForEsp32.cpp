
#include "Model/GeneratorForEsp32.hpp"

#ifdef ESP32

#include "AD9833.h"

GeneratorForEsp32::GeneratorForEsp32(const uint8_t spiCsLine)
    : m_spi(nullptr)
{

    m_AD = new AD9833(spiCsLine, 23, 18);
    if (m_AD != nullptr)
    {
        Serial.println("created AD");
        m_AD->begin();

        while (1)
        {
            m_AD->setFrequency(1000, 0);
            m_AD->setWave(AD9833_SQUARE1);
        }
    }
}

#endif
