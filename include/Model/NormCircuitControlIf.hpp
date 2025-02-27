#ifndef NORMALIZATIONCIRCUITCONTROLIF_HPP
#define NORMALIZATIONCIRCUITCONTROLIF_HPP

#include "ModuleConfig.hpp"

#ifdef USE_NORMALIZATION_CIRCUIT

/*
    Interface to control normalization circuit.
    See /schematics/arduino_uno_application.pdf
*/

class NormCircuitControlIf
{
public:
    virtual void setSwitchChannel1On() = 0;
    virtual void setSwitchChannel2On() = 0;
    virtual void setBothSwitchesOff() = 0;
};

#endif

#endif