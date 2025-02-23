#include "Model/Potentiometer.hpp"
#include "Model/X9C103S_.hpp"

#ifdef USE_X9C103S_POTENTIOMETER_TO_NORMALIZE_WAVEFORMS_AMPLITUDES

Potentiometer::Potentiometer(const uint8_t incPin, const uint8_t udPin, const uint8_t csPin)
{
    m_Potentiometer = new X9C103S_(incPin, udPin, csPin);

    if (m_Potentiometer != nullptr)
    {
        m_Potentiometer->initializePot();
    }
}

void Potentiometer::setSignalStrength(const uint8_t signalStrength)
{
    if (m_Potentiometer != nullptr)
    {
        m_Potentiometer->setResistance(signalStrength);
    }
}

void Potentiometer::setFullSignalStrength()
{
    if (m_Potentiometer != nullptr)
    {
        m_Potentiometer->setToHighest();
    }
}

void Potentiometer::setMinimalSignalStrength()
{
    if (m_Potentiometer != nullptr)
    {
        m_Potentiometer->setToLowest();
    }
}

#endif