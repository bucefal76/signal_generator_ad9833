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
    virtual void setGenerator1Frequency(const long frequency) final;
    virtual long getGenerator1Frequency() const final;
    virtual void setGenerator2Wave(const GeneratorIf::WaveType waveType) final;
    virtual GeneratorIf::WaveType getGenerator2Wave() const final;
    virtual void setGenerator2Frequency(const long frequency) final;
    virtual long getGenerator2Frequency() const final;
    virtual void setStartFrequency(const long startFrequency) final;
    virtual long getStartFrequency() const final;
    virtual void setEndFrequency(const long endFrequency) final;
    virtual long getEndFrequency() const final;

private:
    GeneratorIf::WaveType m_GeneratorChannel1WaveType;
    GeneratorIf::WaveType m_GeneratorChannel2WaveType;
    long m_GeneratorChannel1Frequency;
    long m_GeneratorChannel2Frequency;
    long m_WobbulatorStartFrequency;
    long m_WobbulatorEndFrequency;
};

#endif