#ifndef SERIAL_PORT_VIEW_HPP
#define SERIAL_PORT_VIEW_HPP

#include "ModuleConfig.hpp"

#ifdef USE_SERIAL

#include "View/ViewIf.hpp"

class SerialPortView : public ViewIf
{
public:
    void displayMainMenu() const;
    void displayChannelMenu() const;
    void displayWaveTypeMenu() const;
    void displayFrequencyMenu() const;
    void displayChannelStatus(const uint8_t channelId, const bool channelEnabled, const GeneratorIf::WaveType waveType, const long frequency) const;
    void displayVobulatorMenu() const;
};

#endif

#endif // SERIAL_PORT_VIEW_HPP