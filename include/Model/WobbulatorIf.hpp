#ifndef WOBBULATORIF_HPP
#define WOBBULATORIF_HPP

#include "Model/GeneratorIf.hpp"
#include "Model/SettingsIf.hpp"
#include "Model/RampSignalIf.hpp"

/// @brief Wobbulator interface, defines an abstract class for the Wobbulator
/// @details The Wobbulator implementation classes a class that generates a signal
/// at the generator ouput with different frequencies and and at the same time
/// it generates a ramp signal at DAC output.
/// The abstraction allows to use different Wobbulator implementations in the controller code.
class WobbulatorIf
{
public:
    /// @brief Sets the generator channel used to generate sine sweep signal.
    /// @param generator Pointer to the generator object.
    virtual void setGenerator(GeneratorIf *generator) = 0;
    /// @brief Sets the object that controls the ramp signal.
    virtual void setRampSignal(RampSignalIf *rampSignalSource) = 0;
    /// @brief Sets the pointer to the vobulator settings.
    virtual void setSettingsStorage(SettingsIf *settingsStorage) = 0;
    /// @brief Enable Wobbulator.
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
    /// @brief Sets the start frequency for the Wobbulator sweep
    virtual void setStartFrequency(const long startFrequency) = 0;
    /// @brief Gets the start frequency for Wobbulator sweep
    virtual long getStartFrequency() const = 0;
    /// @brief Sets the end frequency for the Wobbulator sweep
    virtual void setEndFrequency(const long endFrequency) = 0;
    /// @brief Gets the end frequency for Wobbulator sweep
    virtual long getEndFrequency() const = 0;
};

#endif