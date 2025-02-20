#ifndef SERTTINGSIF_HPP
#define SERTTINGSIF_HPP

#include "Model/GeneratorIf.hpp"

/*
    This interface will be used to provide meanings to store settings in not volactall memory (storage).
    Will require different implementations for Arduino Atmel and ESP32.
*/

class SettingsIf
{
public:
    /// @brief Sets to storage generator 1 wave type.
    virtual void setGenerator1Wave(const GeneratorIf::WaveType waveType) = 0;
    /// @brief Gets from storage generator 1 wave type.
    virtual GeneratorIf::WaveType getGenerator1Wave() const = 0;
    /// @brief Sets to storage generator 1 frequency
    virtual void setGenerator1Frequency(const long frequency) = 0;
    /// @brief Gets from storage generator 1 frequency
    virtual long getGenerator1Frequency() const = 0;
    /// @brief Sets to storage generator 2 wave type.
    virtual void setGenerator2Wave(const GeneratorIf::WaveType waveType) = 0;
    /// @brief Gets from storage generator 2 wave type.
    virtual GeneratorIf::WaveType getGenerator2Wave() const = 0;
    /// @brief  Sets to storage  generator 2 frequency
    virtual void setGenerator2Frequency(const long frequency) = 0;
    /// @brief Gets  from storage generator 2 frequency
    virtual long getGenerator2Frequency() const = 0;
    /// @brief Sets to storage wobbulator start frequency.
    virtual void setStartFrequency(const long startFrequency) = 0;
    /// @brief Gets  from storage the start frequency for Wobbulator sweep
    virtual long getStartFrequency() const = 0;
    /// @brief Sets to storage the end frequency for the Wobbulator sweep
    virtual void setEndFrequency(const long endFrequency) = 0;
    /// @brief Gets  from storage the end frequency for Wobbulator sweep
    virtual long getEndFrequency() const = 0;
};

#endif