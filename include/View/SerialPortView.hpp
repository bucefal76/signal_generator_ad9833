#ifndef SERIAL_PORT_VIEW_HPP
#define SERIAL_PORT_VIEW_HPP

#include "ModuleConfig.hpp"

#ifdef USE_SERIAL

#include "View/ViewIf.hpp"

class SerialPortView : public ViewIf
{
public:
    void displayMainMenu(const GeneratorIf *generator1, const GeneratorIf *generator2) const;
    void displayChannelMenu(const GeneratorIf *generator) const;
    void displayWaveTypeMenu(const GeneratorIf *generator) const;
    void displayFrequencyMenu(const GeneratorIf *generator) const;
    void displayVobulatorMenu(const VobulatorIf *vobulator) const;

private:
    void displayChannelStatus(const uint8_t channelId, const bool channelEnabled, const GeneratorIf::WaveType waveType, const long frequency) const;
    void displayVobulatorStatus(const bool isEnabled, const bool isPaused, const long currentFrequency) const;
};

#endif

#endif // SERIAL_PORT_VIEW_HPP