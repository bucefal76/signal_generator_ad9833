#ifndef NORMALIZATIONCIRCUITCONTROLFORNEO_HPP
#define NORMALIZATIONCIRCUITCONTROLFORNEO_HPP

#include "Model/NormCircuitControlIf.hpp"

#ifdef USE_NORMALIZATION_CIRCUIT

class NormCircuitControlForNeo
{
public:
    NormCircuitControlForNeo();

    virtual void setSwitchChannel1On() final;
    virtual void setSwitchChannel2On() final;
    virtual void setBothSwitchesOff() final;
};

#endif

#endif