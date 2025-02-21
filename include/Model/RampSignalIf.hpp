#ifndef WOBULATTORRAMPSIGNALIF_HPP
#define WOBULATTORRAMPSIGNALIF_HPP

#include <Arduino.h>

class RampSignalIf
{

public:
    /// @brief Method sets the ramp signal values with use
    /// the ADC. The used ADC depends on used hardware.
    virtual void setValue(const uint16_t signalValue) = 0;
};

#endif