#ifndef RAMPSIGNALFORUNO_HPP
#define RAMPSIGNALFORUNO_HPP

#include "Model/RampSignalIf.hpp"

#ifndef USE_ESP32

/*
    Class controls the ramp signal for wobbulator.
*/

class RampSignalForUno : public RampSignalIf
{
public:
    RampSignalForUno();

    virtual void setValue(const uint16_t signalValue) final;
};

#endif

#endif