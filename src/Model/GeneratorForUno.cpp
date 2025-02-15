#include "Model/GeneratorForUno.hpp"

#ifndef USE_ESP32

#include "AD9833.h"

GeneratorForUno::GeneratorForUno(const uint8_t spiCsLine)
    : m_AD(nullptr)
{
    m_AD = new AD9833(spiCsLine);
    if (m_AD != nullptr)
    {
        m_AD->begin();
    }
}

GeneratorForUno::~GeneratorForUno()
{
    if (m_AD != nullptr)
    {
        delete m_AD;
    }
}

void GeneratorForUno::setWave(const WaveType type, const uint16_t frequency)
{
    if (m_AD != nullptr)
    {
        switch (type)
        {
        case TypeSinusoidal:
            m_AD->setFrequency(frequency, 0);
            m_AD->setWave(AD9833_SINE);
            break;
        case TypeSquare:
            m_AD->setFrequency(frequency, 0);
            m_AD->setWave(AD9833_SQUARE1);
            break;
        case TypeRamp:
            m_AD->setFrequency(frequency, 0);
            m_AD->setWave(AD9833_TRIANGLE);
            break;
        default:
            m_AD->setFrequency(0, 0);
            m_AD->setWave(AD9833_OFF);
        }
    }
}

bool GeneratorForUno::isEnabled() const
{
    if (m_AD->getWave() != AD9833_OFF)
    {
        return true;
    }

    return false;
}

void GeneratorForUno::disableWave()
{
    if (m_AD != nullptr)
    {
        m_AD->setFrequency(0, 0);
        m_AD->setWave(AD9833_OFF);
    }
}

#endif