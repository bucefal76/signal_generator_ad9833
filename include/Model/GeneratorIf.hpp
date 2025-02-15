#ifndef GENERATORIF_HPP
#define GENERATORIF_HPP

#include <Arduino.h>

/// @brief Interface to define the methods to generate a wave with
/// the any function generator, that implements this interface.
/// The interface is used to abstract the implementation of the
/// function generator, so that the application can use any.
class GeneratorIf
{
public:
    /// @brief Enum to define the type of the wave to generate.
    enum WaveType
    {
        TypeNone,
        TypeSinusoidal,
        TypeSquare,
        TypeRamp
    };

    /// @brief Method to generate a wave, either sinusoidal, square or ramp.
    /// @param type WaveType to generate.
    /// @param frequency Frequency of the wave to generate.
    virtual void generateWave(const WaveType type, const long frequency) = 0;
    /// @brief  Method to disable the wave generation.
    virtual void disableWave() = 0;
    /// @brief Method to get the type of the wave, from the device itself.
    virtual WaveType getWaveType() const = 0;
    /// @brief Method to get the frequency of the wave, from the device itself.
    virtual long getFrequency() const = 0;
    // @brief Method to check if the generator is enabled, from the device itself.
    virtual bool isEnabled() const = 0;
};

#endif