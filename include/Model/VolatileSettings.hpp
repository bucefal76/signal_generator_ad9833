#ifndef VOLATILLESETTINGS_HPP
#define VOLATILLESETTINGS_HPP

#include "SettingsIf.hpp"

class VoltileSettings : public SettingsIf
{
public:
    virtual void setGenerator1Wave(const GeneratorIf::WaveType waveType) final;
    virtual GeneratorIf::WaveType getGenerator1Wave() const final;

    virtual void setGenerator1Frequency(const long frequency) final;
    virtual long getGenerator1Frequency() const final;

    virtual void setGenerator2Wave(const GeneratorIf::WaveType waveType) final;
    virtual GeneratorIf::WaveType getGenerator2Wave() const final;

    virtual void setGenerator2Frequency(const long frequency) final;
    virtual long getGenerator2Frequency() const final;

private:
    GeneratorIf::WaveType m_lastSelectedGeneratorChannel1WaveType;
    GeneratorIf::WaveType m_lastSelectedGeneratorChannel2WaveType;
    long m_lastSelectedGeneratorChannel1Frequency;
    long m_lastSelectedGeneratorChannel2Frequency;
};

#endif