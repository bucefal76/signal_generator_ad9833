#ifndef RAMPSIGNALFORESP32_HPP
#define RAMPSIGNALFORESP32_HPP

#include "Model/RampSignalIf.hpp"

#ifdef USE_ESP32

/*
    Class controls the ramp signal for wobbulator.
    In case of ESP32 the build in DAC is used, channel 0, pin 25.
*/

class RampSignalForEsp32 : public RampSignalIf
{
public:
    RampSignalForEsp32();

    virtual void setValue(const uint16_t signalValue) final;
};

#endif

#endif