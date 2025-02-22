#ifndef POTENTIOMETER_HPP
#define POTENTIOMETER_HPP

#include "Model/PotentiometerIf.hpp"
#include "ModuleConfig.hpp"

#ifdef USE_X9C103S_POTENTIOMETER_TO_NORMALIZE_WAVEFORMS_AMPLITUDES

class Potentiometer : public PotentiometerIf
{
public:
    virtual void setSignalStrenght(const uint8_t signalStrength) final;
};

#endif

#endif