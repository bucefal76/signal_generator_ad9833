#include "Model/GeneratorForUno.hpp"

#ifndef USE_ESP32

#include "AD9833.h"

GeneratorForUno::GeneratorForUno(const uint8_t spiCsLine)
{
    m_AD = new AD9833(spiCsLine);
    if (m_AD != nullptr)
    {
        m_AD->begin();
    }
}

#endif