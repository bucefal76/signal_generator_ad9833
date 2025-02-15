#ifndef GENERATOR_FOR_ESP32_HPP
#define GENERATOR_FOR_ESP32_HPP

#ifdef ESP32

#include "GeneratorIf.hpp"
#include <Arduino.h>

class GeneratorForEsp32 : public GeneratorIf
{
public:
    GeneratorForEsp32(const uint8_t spiCsLine);
    ~GeneratorForEsp32();
    virtual void generateWave(const WaveType type, const long frequency);
    virtual void disableWave();
    virtual long getFrequency() const;
    virtual WaveType getWaveType() const;
    virtual bool isEnabled() const;

private:
    AD9833 *m_AD;
};

#endif

#endif // GENERATOR_FOR_ESP32_HPP