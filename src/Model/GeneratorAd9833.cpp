#include "Model/GeneratorAd9833.hpp"
#include "Model/NormCircuitControlForNeo.hpp"

#include "AD9833.h"

#define POWER_MODE_SLEEP_AL 3U

NormCircuitControlForNeo normCirc;

GeneratorAd9833::GeneratorAd9833(const uint8_t channelId)
    : m_AD(nullptr),
      m_ChannelId(channelId),
      m_Potentiometer(nullptr)
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
    return m_ChannelId;
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
            normCirc.setSwitchChannel1On();
            if (m_Potentiometer != nullptr)
            {
                m_Potentiometer->setFullSignalStrength();
            }
            m_AD->setWave(AD9833_SINE);
            break;
        case TypeSquare:
            normCirc.setSwitchChannel2On();
            if (m_Potentiometer != nullptr)
            {
                m_Potentiometer->setSignalStrength(X9C103S_POTENTIOMETER_SIGNAL_STRENGTH);
            }
            m_AD->setWave(AD9833_SQUARE1);
            break;
        case TypeRamp:
            normCirc.setSwitchChannel1On();
            if (m_Potentiometer != nullptr)
            {
                m_Potentiometer->setFullSignalStrength();
            }
            m_AD->setWave(AD9833_TRIANGLE);
            break;
        default:
            normCirc.setBothSwitchesOff();
            if (m_Potentiometer != nullptr)
            {
                m_Potentiometer->setMinimalSignalStrength();
            }
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

void GeneratorAd9833::connectivityTest()
{
    if (m_AD != nullptr)
    {
        m_AD->setFrequency(TEST_VALUE);

        const float frequency = m_AD->getFrequency();

        if (frequency != TEST_VALUE)
        {
            pinMode(LED_BUILTIN, OUTPUT);

            while (true)
            {
#ifdef USE_SERIAL
                Serial.println("Cannot communicate with one ore more AD9833 generators!");
#endif

                digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
                delay(1000);                     // wait for a second
                digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
                delay(1000);
            }
        }
    }
}

void GeneratorAd9833::setPotentiometer(PotentiometerIf *potentiometer)
{
    m_Potentiometer = potentiometer;
}