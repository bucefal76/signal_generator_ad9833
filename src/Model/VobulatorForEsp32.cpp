#include "Model/VobulatorForEsp32.hpp"

#ifdef USE_ESP32

#include <math.h>
#include <stdint.h>
#include <driver/dac.h>

VobulatorForEsp32 *VobulatorForEsp32::m_Instance = nullptr;

VobulatorForEsp32 *VobulatorForEsp32::getInstance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new VobulatorForEsp32();
    }

    return m_Instance;
}

VobulatorForEsp32::VobulatorForEsp32()
    : m_Generator(nullptr),
      m_startingFrequency(20),
      m_endingFrequency(20000)
{
    setInterval(VOBULATOR_BY_DC_THREAD_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;

    dac_output_enable(DAC_CHANNEL_1); // GPIO25
}

void VobulatorForEsp32::enable()
{
    enabled = true;
}

void VobulatorForEsp32::disable()
{
    enabled = false;
}

void VobulatorForEsp32::update()
{

    if (enabled && m_Generator != nullptr)
    {
        const long frequencyStep = (m_endingFrequency - m_startingFrequency) / RAMP_TABLE_SIZE;
        const uint8_t rampStep = 256 / RAMP_TABLE_SIZE;

        long currentFrequency = m_startingFrequency;
        uint8_t currentRampValue = 0;

        for (int i = 0; i < RAMP_TABLE_SIZE; i++)
        {
            dac_output_voltage(DAC_CHANNEL_1, currentRampValue);
            currentRampValue = currentRampValue + rampStep;

            m_Generator->generateWave(GeneratorIf::TypeSinusoidal, currentFrequency);
            currentFrequency = currentFrequency + frequencyStep;
            delay(100);
        }

        m_Generator->generateWave(GeneratorIf::TypeNone, 0);
        dac_output_voltage(DAC_CHANNEL_1, 0U);
    }
}
void VobulatorForEsp32::setGenerator(GeneratorIf *generator)
{
    m_Generator = generator;
}

void VobulatorForEsp32::onRunCallback()
{
    m_Instance->update();
}

#endif