#include "Model/RampSignalForUno.hpp"

#ifndef USE_ESP32

#include "ModuleConfig.hpp"
#include "Wire.h"
#include "MCP4725.h"

RampSignalForUno::RampSignalForUno()
    : m_Dac(nullptr)
{
    Wire.begin();

    m_Dac = new MCP4725(WOBBULATOR_RAMP_SIGNAL_ADC_I2C_ADDRESS);

    if (m_Dac != nullptr)
    {
        if (m_Dac->begin())
        {
            m_Dac->setValue(0U);
        }
        else
        {
            pinMode(LED_BUILTIN, OUTPUT);

            while (true)
            {
#ifdef USE_SERIAL
                Serial.println("Cannot communicate with the MCP 4725 DAC!");
#endif

                digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
                delay(1000);                     // wait for a second
                digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
                delay(1000);
            }
        }
    }
}

void RampSignalForUno::setValue(const uint16_t signalValue)
{
    if (m_Dac != nullptr)
    {
        m_Dac->setValue(signalValue);
    }
}

#endif