
#ifndef GENERATORIF_HPP
#define GENERATORIF_HPP

#include <Arduino.h>

class GeneratorIf
{
public:
    enum GetTypes
    {
        TypeSinusoidal,
        TypeSquare,
        TypeRamp
    };

    virtual void enableGenerator(const GetTypes type, const uint16_t frequency) = 0;
    virtual void disableGenerator() = 0;
};

#endif