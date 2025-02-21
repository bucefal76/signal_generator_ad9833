#include "Model/RampSignalForUno.hpp"

#ifndef USE_ESP32

#include "Wire.h"
#include "MCP4725.h"

MCP4725 MCP(0x60);

RampSignalForUno::RampSignalForUno()
{
    Wire.begin();

    MCP.begin();
    MCP.setValue(1000);
}

void RampSignalForUno::setValue(const uint16_t signalValue)
{
    MCP.setValue(signalValue * 10);
}

#endif