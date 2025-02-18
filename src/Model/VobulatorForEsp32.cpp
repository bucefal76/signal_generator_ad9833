#include "Model/VobulatorForEsp32.hpp"

#ifdef USE_ESP32

#include <math.h>
#include <stdint.h>
#include <driver/dac.h>

#define VOBULATOR_MAX_FREQUENCY 12500000U
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
      m_startFrequency(500),
      m_endFrequency(20000),
      m_currentStep(VOBULATOR_RAMP_FIRST_STEP),
      m_frequencyStep(1U),
      m_isPaused(false)
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

        m_frequencyStep = (m_endFrequency - m_startFrequency) / VOBULATOR_NUMBER_OF_STEPS;

        m_isPaused = false;
        enabled = true;
    }
}

void VobulatorForEsp32::disable()
{
    enabled = false;
    m_isPaused = false;
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

            const long frequency = m_startFrequency + m_currentStep * m_frequencyStep;
            m_Generator->generateWave(GeneratorIf::TypeSinusoidal, frequency);

            if (false == m_isPaused)
            {
                m_currentStep++;
            }
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

void VobulatorForEsp32::pause()
{
    m_isPaused = true;
}

void VobulatorForEsp32::resume()
{
    m_isPaused = false;
}

void VobulatorForEsp32::stepUp()
{
    if (m_isPaused)
    {
        m_currentStep++;
        if (m_currentStep >= VOBULATOR_NUMBER_OF_STEPS)
        {
            m_currentStep = VOBULATOR_NUMBER_OF_STEPS - 1;
        }
    }
}

void VobulatorForEsp32::stepDown()
{
    if (m_isPaused)
    {
        if (m_currentStep == VOBULATOR_RAMP_FIRST_STEP)
        {
            m_currentStep = VOBULATOR_RAMP_FIRST_STEP;
        }
        else
        {
            m_currentStep--;
        }
    }
}

long VobulatorForEsp32::getCurrentFrequency() const
{
    return m_startFrequency + m_currentStep * m_frequencyStep;
}

bool VobulatorForEsp32::isEnabled() const
{
    return enabled;
}

bool VobulatorForEsp32::isPaused() const
{
    return m_isPaused;
}

long VobulatorForEsp32::getStartFrequency() const
{
    return m_startFrequency;
}

long VobulatorForEsp32::getEndFrequency() const
{
    return m_endFrequency;
}

void VobulatorForEsp32::setStartFrequency(const long startFrequency)
{
    if ((startFrequency > 0) && (startFrequency < VOBULATOR_MAX_FREQUENCY))
    {
        if (startFrequency < m_endFrequency)
        {
            m_startFrequency = startFrequency;
        }
    }
}

void VobulatorForEsp32::setEndFrequency(const long endFrequency)
{
    if ((endFrequency > 0) && (endFrequency <= VOBULATOR_MAX_FREQUENCY))
    {
        if (m_startFrequency < endFrequency)
        {
            m_endFrequency = endFrequency;
        }
    }
}

#endif