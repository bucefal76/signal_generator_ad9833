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
    virtual void displayMainMenu() = 0;
    /// @brief Display the channel menu.
    virtual void displayChannelMenu() = 0;
    /// @brief Display the wave type menu.
    virtual void displayWaveTypeMenu() = 0;
    /// @brief Display the frequency menu.
    virtual void displayFrequencyMenu() = 0;
    /// @brief Display the status of the channel.
    /// @param channelId The channel ID to display.
    /// @param channelEnabled Display if the channel is enabled or disabled.
    /// @param waveType Displays the type of wave.
    /// @param frequency Displays the frequency of the wave.
    virtual void displayChannelStatus(const uint8_t channelId, const bool channelEnabled, const GeneratorIf::WaveType waveType, const long frequency) = 0;
};

#endif // VIEWIF_HPP