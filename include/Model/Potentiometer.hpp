#ifndef POTENTIOMETER_HPP
#define POTENTIOMETER_HPP

#include "Model/PotentiometerIf.hpp"
#include "ModuleConfig.hpp"

#ifdef USE_X9C103S_POTENTIOMETER_TO_NORMALIZE_WAVEFORMS_AMPLITUDES

#include <X9C103S.h>

class Potentiometer : public PotentiometerIf
{
public:
    Potentiometer(const uint8_t incPin, const uint8_t udPin, const uint8_t csPin);
    virtual void setSignalStrength(const uint8_t signalStrength) final;
    virtual void setFullSignalStrength() final;
    virtual void setMinimalSignalStrength() final;

private:
    X9C103S *m_Potentiometer;
};

#endif

#endif