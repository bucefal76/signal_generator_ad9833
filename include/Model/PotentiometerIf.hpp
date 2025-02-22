#ifndef POTENTIOMETERIF_HPP
#define POTENTIOMETERIF_HPP

class PotentiometerIf
{
public:
    virtual void setSignalStrenght(const uint8_t signalStrength) = 0;
};

#endif