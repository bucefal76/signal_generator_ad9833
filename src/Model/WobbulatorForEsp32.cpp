#include "Model/WobbulatorForEsp32.hpp"

#ifdef USE_ESP32

#include <math.h>
#include <stdint.h>
#include <driver/dac.h>

#define VOBULATOR_MAX_FREQUENCY 12500000U
#define VOBULATOR_RAMP_FIRST_STEP 0U
// DAC resolution is 8 bits, so 256 steps
#define VOBULATOR_RAMP_STEP (256 / VOBULATOR_NUMBER_OF_STEPS)

WobbulatorForEsp32 *WobbulatorForEsp32::m_Instance = nullptr;

WobbulatorForEsp32 *WobbulatorForEsp32::getInstance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new WobbulatorForEsp32();
    }

    return m_Instance;
}

WobbulatorForEsp32::WobbulatorForEsp32()
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

void WobbulatorForEsp32::enable()
{
    if (m_Generator != nullptr)
    {
        dac_output_voltage(DAC_CHANNEL_1, 0U);
        m_Generator->disableWave();

        m_currentStep = VOBULATOR_RAMP_FIRST_STEP;

        m_frequencyStep = (m_endFrequency - m_startFrequency) / VOBULATOR_NUMBER_OF_STEPS;

        m_isPaused = false;
        enabled = true;
    }
}

void WobbulatorForEsp32::disable()
{
    enabled = false;
    m_isPaused = false;
    dac_output_voltage(DAC_CHANNEL_1, 0U);
    m_Generator->disableWave();
}

void WobbulatorForEsp32::update()
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

void WobbulatorForEsp32::setGenerator(GeneratorIf *generator)
{
    m_Generator = generator;
}

void WobbulatorForEsp32::onRunCallback()
{
    m_Instance->update();
}

void WobbulatorForEsp32::pause()
{
    m_isPaused = true;
}

void WobbulatorForEsp32::resume()
{
    m_isPaused = false;
}

void WobbulatorForEsp32::stepUp()
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

void WobbulatorForEsp32::stepDown()
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

long WobbulatorForEsp32::getCurrentFrequency() const
{
    return m_startFrequency + m_currentStep * m_frequencyStep;
}

bool WobbulatorForEsp32::isEnabled() const
{
    return enabled;
}

bool WobbulatorForEsp32::isPaused() const
{
    return m_isPaused;
}

long WobbulatorForEsp32::getStartFrequency() const
{
    return m_startFrequency;
}

long WobbulatorForEsp32::getEndFrequency() const
{
    return m_endFrequency;
}

void WobbulatorForEsp32::setStartFrequency(const long startFrequency)
{
    if ((startFrequency > 0) && (startFrequency < VOBULATOR_MAX_FREQUENCY))
    {
        if (startFrequency < m_endFrequency)
        {
            m_startFrequency = startFrequency;
        }
    }
}

void WobbulatorForEsp32::setEndFrequency(const long endFrequency)
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