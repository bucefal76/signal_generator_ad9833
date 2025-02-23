#ifndef POTENTIOMETERIF_HPP
#define POTENTIOMETERIF_HPP

#include <Arduino.h>

class PotentiometerIf
{
public:
    virtual void setSignalStrength(const uint8_t signalStrength) = 0;
    virtual void setFullSignalStrength() = 0;
    virtual void setMinimalSignalStrength() = 0;
};

#endif