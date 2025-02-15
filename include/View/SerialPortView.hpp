#ifndef SERIAL_PORT_VIEW_HPP
#define SERIAL_PORT_VIEW_HPP

#include "ModuleConfig.hpp"

#ifdef USE_SERIAL

#include "View/ViewIf.hpp"

class SerialPortView : public ViewIf
{
public:
    void displayMainMenu();
    void displayChannelMenu();
    void displayWaveTypeMenu();
    void displayFrequencyMenu();
    void displayChannelStatus(const uint8_t channelId, const bool channelEnabled, const GeneratorIf::WaveType waveType, const long frequency);
};

#endif

#endif // SERIAL_PORT_VIEW_HPP