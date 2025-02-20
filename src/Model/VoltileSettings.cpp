#include "Model/VolatileSettings.hpp"

VoltileSettings::VoltileSettings()
    : m_lastSelectedGeneratorChannel1WaveType(GeneratorIf::TypeSquare),
      m_lastSelectedGeneratorChannel2WaveType(GeneratorIf::TypeSquare),
      m_lastSelectedGeneratorChannel1Frequency(1000),
      m_lastSelectedGeneratorChannel2Frequency(500),
      m_wobbulatorStartFrequency(500),
      m_wobbulatorEndFrequency(20000)
{
}

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

void VoltileSettings::setStartFrequency(const long startFrequency)
{
    m_wobbulatorStartFrequency = startFrequency;
}

long VoltileSettings::getStartFrequency() const
{
    return m_wobbulatorStartFrequency;
}

void VoltileSettings::setEndFrequency(const long endFrequency)
{
    m_wobbulatorEndFrequency = endFrequency;
}

long VoltileSettings::getEndFrequency() const
{
    return m_wobbulatorEndFrequency;
}