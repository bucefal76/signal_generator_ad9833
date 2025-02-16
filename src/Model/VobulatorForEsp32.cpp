#include "Model/VobulatorForEsp32.hpp"

#ifdef USE_ESP32

#include <math.h>
#include <stdint.h>
#include <driver/dac.h>

#define VOBULATOR_RAMP_FIRST_STEP 0U
// DAC resolution is 8 bits, so 256 steps
#define VOBULATOR_RAMP_STEP (256 / VOBULATOR_NUMBER_OF_STEPS)

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
      m_startingFrequency(200),
      m_endingFrequency(20000),
      m_currentStep(VOBULATOR_RAMP_FIRST_STEP),
      m_frequencyStep(1U)
{
    setInterval(VOBULATOR_BY_DC_THREAD_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;

    dac_output_enable(DAC_CHANNEL_1); // GPIO25
}

void VobulatorForEsp32::enable()
{
    if (m_Generator != nullptr)
    {
        m_currentStep = VOBULATOR_RAMP_FIRST_STEP;

        m_frequencyStep = (m_endingFrequency - m_startingFrequency) / VOBULATOR_NUMBER_OF_STEPS;

        enabled = true;
    }
}

void VobulatorForEsp32::disable()
{
    enabled = false;
    dac_output_voltage(DAC_CHANNEL_1, 0U);
    m_Generator->disableWave();
}

void VobulatorForEsp32::update()
{
    if (enabled && m_Generator != nullptr)
    {
        if (m_currentStep < VOBULATOR_NUMBER_OF_STEPS)
        {
            const uint8_t rampDcValue = m_currentStep * VOBULATOR_RAMP_STEP;
            dac_output_voltage(DAC_CHANNEL_1, rampDcValue);

            const long frequency = m_startingFrequency + m_currentStep * m_frequencyStep;
            m_Generator->generateWave(GeneratorIf::TypeSinusoidal, frequency);

            m_currentStep++;
        }
        else
        {
            m_currentStep = VOBULATOR_RAMP_FIRST_STEP;
        }
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