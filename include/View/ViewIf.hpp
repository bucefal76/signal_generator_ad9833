#ifndef VIEWIF_HPP
#define VIEWIF_HPP

#include <Arduino.h>
#include "Model/GeneratorIf.hpp"
#include "Model/WobbulatorIf.hpp"

/// @brief Interface to define the methods to display messages to the operator.
/// The interface is used to abstract the implementation of the view from
/// the controller, so that the controller can use any view.
class ViewIf
{
public:
    enum WobbulatorFrequency
    {
        FrequencyStart,
        FrequencyEnd
    };

    /// @brief Display the main menu.
    virtual void
    displayMainMenu(const GeneratorIf *generator1, const GeneratorIf *generator2) const = 0;
    /// @brief Display the channel menu.
    virtual void displayGeneratorChannelMenu(const GeneratorIf *generator) const = 0;
    /// @brief Display the wave type menu.
    virtual void displayGeneratorWaveTypeSelectionMenu(const GeneratorIf *generator) const = 0;
    /// @brief Display the frequency menu.
    virtual void displayGeneratorFrequencySelectionMenu(const GeneratorIf *generator) const = 0;
    /// @brief Display the Wobbulator menu.
    virtual void displayWobbulatorMenu(const WobbulatorIf *wobbulator) const = 0;
    /// @brief Displays the Wobbulator frequency selection menu
    virtual void displayWobbulatorFrequencySelectionMenu(const WobbulatorIf *wobbulator, const WobbulatorFrequency frequencyType) const = 0;
};

#endif // VIEWIF_HPP