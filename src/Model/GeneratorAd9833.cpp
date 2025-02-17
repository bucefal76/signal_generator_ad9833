#include "Model/GeneratorAd9833.hpp"

#include "AD9833.h"

#define POWER_MODE_SLEEP_AL 3U

GeneratorAd9833::GeneratorAd9833(const uint8_t channelId)
    : m_AD(nullptr), m_channelId(channelId)
{
}

GeneratorAd9833::~GeneratorAd9833()
{
    if (m_AD != nullptr)
    {
        delete m_AD;
    }
}

uint8_t GeneratorAd9833::getChannelId() const
{
    return m_channelId;
}

void GeneratorAd9833::generateWave(const WaveType type, const long frequency)
{
    if (m_AD != nullptr)
    {
        m_AD->setPowerMode();
        m_AD->setFrequency(frequency, 0);

        switch (type)
        {
        case TypeSinusoidal:
            m_AD->setWave(AD9833_SINE);
            break;
        case TypeSquare:

            m_AD->setWave(AD9833_SQUARE1);
            break;
        case TypeRamp:
            m_AD->setWave(AD9833_TRIANGLE);
            break;
        default:
            m_AD->setFrequency(0, 0);
            m_AD->setWave(AD9833_OFF);
        }
    }
}

GeneratorIf::WaveType GeneratorAd9833::getWaveType() const
{
    if (m_AD != nullptr)
    {
        switch (m_AD->getWave())
        {
        case AD9833_SINE:
            return TypeSinusoidal;
        case AD9833_SQUARE1:
            return TypeSquare;
        case AD9833_TRIANGLE:
            return TypeRamp;
        default:
            return TypeNone;
        }
    }

    return TypeNone;
}

long GeneratorAd9833::getFrequency() const
{
    if (m_AD != nullptr)
    {
        return m_AD->getFrequency(0);
    }

    return 0U;
}

bool GeneratorAd9833::isEnabled() const
{
    if (m_AD->getWave() != AD9833_OFF)
    {
        return true;
    }

    return false;
}

void GeneratorAd9833::disableWave()
{
    if (m_AD != nullptr)
    {
        m_AD->setFrequency(0, 0);
        m_AD->setWave(AD9833_OFF);
        m_AD->setPowerMode(POWER_MODE_SLEEP_AL);
    }
}