#ifndef VIEWIF_HPP
#define VIEWIF_HPP

#include <Arduino.h>
#include "Model/GeneratorIf.hpp"

/// @brief Interface to define the methods to display messages to the operator.
/// The interface is used to abstract the implementation of the view from
/// the controller, so that the controller can use any view.
class ViewIf
{
public:
    /// @brief Display the main menu.
    virtual void displayMainMenu(const GeneratorIf *generator1, const GeneratorIf *generator2) const = 0;
    /// @brief Display the channel menu.
    virtual void displayChannelMenu(const GeneratorIf *generator) const = 0;
    /// @brief Display the wave type menu.
    virtual void displayWaveTypeMenu(const GeneratorIf *generator) const = 0;
    /// @brief Display the frequency menu.
    virtual void displayFrequencyMenu(const GeneratorIf *generator) const = 0;

    /// @brief Display the vobulator menu.
    virtual void displayVobulatorMenu() const = 0;
};

#endif // VIEWIF_HPP