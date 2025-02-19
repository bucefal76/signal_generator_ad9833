#ifndef SERTTINGSIF_HPP
#define SERTTINGSIF_HPP

#include "Model/GeneratorIf.hpp"

/*
    This interface will be used to provide meanings to store settings in not volactall memory.
    Will require different implementations for Arduino Atmel and ESP32.
*/

class SettingsIf
{
public:
    virtual void setGenerator1Wave(const GeneratorIf::WaveType waveType) = 0;
    virtual GeneratorIf::WaveType getGenerator1Wave() const = 0;

    virtual void setGenerator1Frequency(const long frequency) = 0;
    virtual long getGenerator1Frequency() const = 0;

    virtual void setGenerator2Wave(const GeneratorIf::WaveType waveType) = 0;
    virtual GeneratorIf::WaveType getGenerator2Wave() const = 0;

    virtual void setGenerator2Frequency(const long frequency) = 0;
    virtual long getGenerator2Frequency() const = 0;
};

#endif