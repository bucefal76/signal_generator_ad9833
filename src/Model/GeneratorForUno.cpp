#include "Model/GeneratorForUno.hpp"

#ifndef USE_ESP32

#include "AD9833.h"

GeneratorForUno::GeneratorForUno(const uint8_t spiCsLine)
    : m_AD(nullptr)
{
    m_AD = new AD9833(spiCsLine);
    m_AD->begin();
}

void GeneratorForUno::enableGenerator(const GetTypes type, const uint16_t frequency)
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

void GeneratorForUno::disableGenerator()
{
    m_AD->setFrequency(0, 0);
    m_AD->setWave(AD9833_OFF);
}

#endif