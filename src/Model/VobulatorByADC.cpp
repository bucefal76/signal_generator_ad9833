#include "Model/VobulatorByADC.hpp"
#include "ModuleConfig.hpp"

/*
const int dacPin = 25; // Define the DAC pin (GPIO 25 in this example)

void setup() {
  // No need for serial communication setup in this example
}

void loop() {
  for (int value = 0; value <= 255; value++) { // Loop through values from 0 to 255
    dacWrite(dacPin, value); // Write the analog value to the DAC pin
    delay(10); // Wait for 10 milliseconds before writing the next value
  }
  for (int value = 255; value >= 0; value--) { // Loop through values from 255 to 0
    dacWrite(dacPin, value); // Write the analog value to the DAC pin
    delay(10); // Wait for 10 milliseconds before writing the next value
  }
}
  */

#define DAC_PIN 25

VobulatorByADC *VobulatorByADC::m_Instance = nullptr;

VobulatorByADC *VobulatorByADC::getInstance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new VobulatorByADC();
    }

    return m_Instance;
}

VobulatorByADC::VobulatorByADC()
{
    setInterval(VOBULATOR_BY_DC_THREAD_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;

    state = true;
}

void VobulatorByADC::enable()
{
    enabled = true;
}

void VobulatorByADC::disable()
{
    enabled = false;
}

void VobulatorByADC::update()
{
    if (state)
    {
        dacWrite(DAC_PIN, 0xFF);
    }
    else
    {
        dacWrite(DAC_PIN, 0x00);
    }

    state = !state;

    Serial.println(F("CLICK"));
}

void VobulatorByADC::onRunCallback()
{
    m_Instance->update();
}
