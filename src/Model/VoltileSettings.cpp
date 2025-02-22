#include "Model/VolatileSettings.hpp"

VoltileSettings::VoltileSettings()
    : m_GeneratorChannel1WaveType(GeneratorIf::TypeSquare),
      m_GeneratorChannel2WaveType(GeneratorIf::TypeSquare),
      m_GeneratorChannel1Frequency(1000),
      m_GeneratorChannel2Frequency(500),
      m_WobbulatorStartFrequency(500),
      m_WobbulatorEndFrequency(20000)
{
}

void VoltileSettings::setGenerator1Wave(const GeneratorIf::WaveType waveType)
{
    m_GeneratorChannel1WaveType = waveType;
}

GeneratorIf::WaveType VoltileSettings::getGenerator1Wave() const
{
    return m_GeneratorChannel1WaveType;
}

void VoltileSettings::setGenerator1Frequency(const unsigned long frequency)
{
    m_GeneratorChannel1Frequency = frequency;
}

unsigned long VoltileSettings::getGenerator1Frequency() const
{
    return m_GeneratorChannel1Frequency;
}

void VoltileSettings::setGenerator2Wave(const GeneratorIf::WaveType waveType)
{
    m_GeneratorChannel2WaveType = waveType;
}

GeneratorIf::WaveType VoltileSettings::getGenerator2Wave() const
{
    return m_GeneratorChannel2WaveType;
}

void VoltileSettings::setGenerator2Frequency(const unsigned long frequency)
{
    m_GeneratorChannel2Frequency = frequency;
}

unsigned long VoltileSettings::getGenerator2Frequency() const
{
    return m_GeneratorChannel2Frequency;
}

void VoltileSettings::setStartFrequency(const unsigned long startFrequency)
{
    m_WobbulatorStartFrequency = startFrequency;
}

unsigned long VoltileSettings::getStartFrequency() const
{
    return m_WobbulatorStartFrequency;
}

void VoltileSettings::setEndFrequency(const unsigned long endFrequency)
{
    m_WobbulatorEndFrequency = endFrequency;
}

unsigned long VoltileSettings::getEndFrequency() const
{
    return m_WobbulatorEndFrequency;
}