
#ifndef GENERATORIF_HPP
#define GENERATORIF_HPP

#include <Arduino.h>

class GeneratorIf
{
public:
    enum WaveType
    {
        TypeNone,
        TypeSinusoidal,
        TypeSquare,
        TypeRamp
    };

    virtual void setWave(const WaveType type, const uint16_t frequency) = 0;
    virtual bool isEnabled() const = 0;
    virtual void disableWave() = 0;
};

#endif