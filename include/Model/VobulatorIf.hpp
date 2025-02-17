#ifndef VOBULATORIF_HPP
#define VOBULATORIF_HPP

#include "Model/GeneratorIf.hpp"

/// @brief Vobulator interface, defines an abstract class for the Vobulator
/// @details The Vobulator implementation classes a class that generates a signal
/// at the generator ouput with different frequencies and and at the same time
/// it generates a ramp signal at DAC output.
/// The abstraction allows to use different Vobulator implementations in the controller code.
class VobulatorIf
{
public:
    /// @brief Sets the generator channel used to generate sine sweep signal.
    /// @param generator Pointer to the generator object.
    virtual void setGenerator(GeneratorIf *generator) = 0;
    /// @brief Enable vobulator.
    virtual void enable() = 0;
    /// @brief Disable generator.
    virtual void disable() = 0;
    /// @brief Pause auto step
    virtual void pause() = 0;
    /// @brief Resume auto step.
    virtual void resume() = 0;
    /// @brief Manual Step UP
    virtual void stepUp() = 0;
    /// @brief Manual step DOWN;
    virtual void stepDown() = 0;
    /// @brief Returns value of the current frequency.
    virtual long getCurrentFrequency() const = 0;
    /// @brief Returns true if is enabled
    virtual bool isEnabled() const = 0;
    /// @brief Returns true if auto step is disabled
    virtual bool isPaused() const = 0;
};

#endif