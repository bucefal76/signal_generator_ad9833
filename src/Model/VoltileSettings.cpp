#include "Model/VolatileSettings.hpp"

void VoltileSettings::setGenerator1Wave(const GeneratorIf::WaveType waveType)
{
    m_lastSelectedGeneratorChannel1WaveType = waveType;
}

GeneratorIf::WaveType VoltileSettings::getGenerator1Wave() const
{
    return m_lastSelectedGeneratorChannel1WaveType;
}

void VoltileSettings::setGenerator1Frequency(const long frequency)
{
    m_lastSelectedGeneratorChannel1Frequency = frequency;
}

long VoltileSettings::getGenerator1Frequency() const
{
    return m_lastSelectedGeneratorChannel1Frequency;
}

void VoltileSettings::setGenerator2Wave(const GeneratorIf::WaveType waveType)
{
    m_lastSelectedGeneratorChannel2WaveType = waveType;
}

GeneratorIf::WaveType VoltileSettings::getGenerator2Wave() const
{
    return m_lastSelectedGeneratorChannel2WaveType;
}

void VoltileSettings::setGenerator2Frequency(const long frequency)
{
    m_lastSelectedGeneratorChannel2Frequency = frequency;
}

long VoltileSettings::getGenerator2Frequency() const
{
    return m_lastSelectedGeneratorChannel2Frequency;
}