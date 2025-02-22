#ifndef VOLATILLESETTINGS_HPP
#define VOLATILLESETTINGS_HPP

#include "SettingsIf.hpp"

/*
    This class implements the SettingsIf inteface, the settings storage.
    The current implementation is volatile, so it does not storage any setthins
    between device sessions.
*/

class VoltileSettings : public SettingsIf
{
public:
    VoltileSettings();
    virtual void setGenerator1Wave(const GeneratorIf::WaveType waveType) final;
    virtual GeneratorIf::WaveType getGenerator1Wave() const final;
    virtual void setGenerator1Frequency(const unsigned long frequency) final;
    virtual unsigned long getGenerator1Frequency() const final;
    virtual void setGenerator2Wave(const GeneratorIf::WaveType waveType) final;
    virtual GeneratorIf::WaveType getGenerator2Wave() const final;
    virtual void setGenerator2Frequency(const unsigned long frequency) final;
    virtual unsigned long getGenerator2Frequency() const final;
    virtual void setStartFrequency(const unsigned long startFrequency) final;
    virtual unsigned long getStartFrequency() const final;
    virtual void setEndFrequency(const unsigned long endFrequency) final;
    virtual unsigned long getEndFrequency() const final;

private:
    GeneratorIf::WaveType m_GeneratorChannel1WaveType;
    GeneratorIf::WaveType m_GeneratorChannel2WaveType;
    unsigned long m_GeneratorChannel1Frequency;
    unsigned long m_GeneratorChannel2Frequency;
    unsigned long m_WobbulatorStartFrequency;
    unsigned long m_WobbulatorEndFrequency;
};

#endif