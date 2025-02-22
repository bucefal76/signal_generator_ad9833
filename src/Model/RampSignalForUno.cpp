#include "Model/RampSignalForUno.hpp"

#ifndef USE_ESP32

#include "ModuleConfig.hpp"
#include "Wire.h"
#include "MCP4725.h"

MCP4725 MCP(WOBBULATOR_RAMP_SIGNAL_ADC_I2C_ADDRESS);

RampSignalForUno::RampSignalForUno()
{
    Wire.begin();

    if (MCP.begin())
    {
        MCP.setValue(0U);
    }
    else
    {
        pinMode(LED_BUILTIN, OUTPUT);

        while (true)
        {
#ifdef USE_SERIAL
            Serial.println("Cannot communicate with one ore more AD9833 generators!");
#endif

            digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
            delay(1000);                     // wait for a second
            digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
            delay(1000);
        }
    }
}

void RampSignalForUno::setValue(const uint16_t signalValue)
{
    MCP.setValue(signalValue);
}

#endif