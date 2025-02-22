#include "Model/RampSignalForUno.hpp"

#ifndef USE_ESP32

#include "ModuleConfig.hpp"
#include "Wire.h"
#include "MCP4725.h"

MCP4725 MCP(WOBBULATOR_RAMP_SIGNAL_ADC_I2C_ADDRESS);

RampSignalForUno::RampSignalForUno()
{
    Wire.begin();

    MCP.begin();
    MCP.setValue(0U);
}

void RampSignalForUno::setValue(const uint16_t signalValue)
{
    MCP.setValue(signalValue);
}

#endif