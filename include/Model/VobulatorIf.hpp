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

    virtual void enable() = 0;
    virtual void disable() = 0;
};

#endif