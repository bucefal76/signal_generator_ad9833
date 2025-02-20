#ifndef SERIAL_PORT_VIEW_HPP
#define SERIAL_PORT_VIEW_HPP

#include "ModuleConfig.hpp"

#ifdef USE_SERIAL

#include "View/ViewIf.hpp"

class SerialPortView : public ViewIf
{
public:
    void displayMainMenu(const GeneratorIf *generator1, const GeneratorIf *generator2, const WobbulatorIf *wobbulator = nullptr) const final;
    void displayGeneratorChannelMenu(const GeneratorIf *generator) const final;
    void displayGeneratorWaveTypeSelectionMenu(const GeneratorIf *generator) const;
    void displayGeneratorFrequencySelectionMenu(const GeneratorIf *generator) const final;
    void displayWobbulatorMenu(const WobbulatorIf *woobulator) const final;
    void displayWobbulatorFrequencySelectionMenu(const WobbulatorIf *woobulator, const ViewIf::WobbulatorFrequency frequencyType) const final;

private:
    void displayChannelStatus(const uint8_t channelId, const bool channelEnabled, const GeneratorIf::WaveType waveType, const long frequency) const;
    void displayWobbulatorStatus(const bool isEnabled, const bool isPaused, const long currentFrequency, const long startFrequency, const long endFrequency) const;
};

#endif

#endif // SERIAL_PORT_VIEW_HPP