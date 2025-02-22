#include "Model/RampSignalForEsp32.hpp"

#ifdef USE_ESP32

#include <driver/dac.h>

RampSignalForEsp32::RampSignalForEsp32()
{
    dac_output_enable(DAC_CHANNEL_1); // GPIO25
}

void RampSignalForEsp32::setValue(const uint16_t signalValue)
{
    dac_output_voltage(DAC_CHANNEL_1, signalValue);
}

#endif