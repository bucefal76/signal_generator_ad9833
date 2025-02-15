
#include "Model/GeneratorForEsp32.hpp"

#ifdef ESP32

#include "AD9833.h"

GeneratorForEsp32::GeneratorForEsp32(const uint8_t spiCsLine)
    : m_spi(nullptr)
{
    /*
        m_spi = new SPIClass(VSPI);
        m_AD = new AD9833(5, m_spi);
        m_spi->begin();

        m_AD->begin();
        m_AD->setSPIspeed(10000000);
    */
    /*
    while (1)
    {

        m_AD->setFrequency(1000, 0);
        m_AD->setWave(AD9833_SQUARE1);
    }
        */

    m_AD = new AD9833(12, 23, 18);
    if (m_AD != nullptr)
    {
        m_AD->begin();
    }
}

#endif
