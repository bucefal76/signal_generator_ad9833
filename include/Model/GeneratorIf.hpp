#ifndef GENERATORIF_HPP
#define GENERATORIF_HPP

#include <Arduino.h>
#include "Model/PotentiometerIf.hpp"
#include "Model/NormCircuitControlIf.hpp"

/// @brief Interface to define the methods to generate a wave with
/// the any function generator, that implements this interface.
/// The interface is used to abstract the implementation of the
/// function generator, so that the controller can use any.
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

    /// @brief Method to get the channel id of the generator.
    virtual uint8_t getChannelId() const = 0;
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
    /// @brief Sets the pointer to the potentiometer object to normalize the signals
    /// @param potentiometer Pointer to the PotentiometerIf type object.
    virtual void setPotentiometer(PotentiometerIf *potentiometer) = 0;
    /// @brief Sets the pointer to the normalization circuit controller, see NormCircuitControlIf.
    virtual void setNormalizationCircuitController(NormCircuitControlIf *normCircuitController) = 0;
};

#endif