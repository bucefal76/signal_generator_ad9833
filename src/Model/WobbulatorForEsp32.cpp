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
      m_Settings(nullptr),
      m_CurrentStepNo(VOBULATOR_RAMP_FIRST_STEP),
      m_FrequencyStep(1U),
      m_IsPaused(false)
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

        m_CurrentStepNo = VOBULATOR_RAMP_FIRST_STEP;

        m_FrequencyStep = (m_Settings->getEndFrequency() - m_Settings->getStartFrequency()) / VOBULATOR_NUMBER_OF_STEPS;

        m_IsPaused = false;
        enabled = true;
    }
}

void WobbulatorForEsp32::disable()
{
    enabled = false;
    m_IsPaused = false;
    dac_output_voltage(DAC_CHANNEL_1, 0U);
    m_Generator->disableWave();
}

void WobbulatorForEsp32::update()
{
    if (enabled && m_Generator != nullptr)
    {
        if (m_CurrentStepNo < VOBULATOR_NUMBER_OF_STEPS)
        {
            const uint8_t rampDcValue = m_CurrentStepNo * VOBULATOR_RAMP_STEP;
            dac_output_voltage(DAC_CHANNEL_1, rampDcValue);

            const long frequency = m_Settings->getStartFrequency() + (m_CurrentStepNo * m_FrequencyStep);
            m_Generator->generateWave(GeneratorIf::TypeSinusoidal, frequency);

            if (false == m_IsPaused)
            {
                m_CurrentStepNo++;
            }
        }
        else
        {
            m_CurrentStepNo = VOBULATOR_RAMP_FIRST_STEP;
        }
    }
}

void WobbulatorForEsp32::setGenerator(GeneratorIf *generator)
{
    m_Generator = generator;
}

void WobbulatorForEsp32::setsSettingsStorage(SettingsIf *settingsStorage)
{
    m_Settings = settingsStorage;
}

void WobbulatorForEsp32::onRunCallback()
{
    m_Instance->update();
}

void WobbulatorForEsp32::pause()
{
    m_IsPaused = true;
}

void WobbulatorForEsp32::resume()
{
    m_IsPaused = false;
}

void WobbulatorForEsp32::stepUp()
{
    if (m_IsPaused)
    {
        m_CurrentStepNo++;
        if (m_CurrentStepNo >= VOBULATOR_NUMBER_OF_STEPS)
        {
            m_CurrentStepNo = VOBULATOR_NUMBER_OF_STEPS - 1;
        }
    }
}

void WobbulatorForEsp32::stepDown()
{
    if (m_IsPaused)
    {
        if (m_CurrentStepNo == VOBULATOR_RAMP_FIRST_STEP)
        {
            m_CurrentStepNo = VOBULATOR_RAMP_FIRST_STEP;
        }
        else
        {
            m_CurrentStepNo--;
        }
    }
}

long WobbulatorForEsp32::getCurrentFrequency() const
{
    return m_Settings->getStartFrequency() + m_CurrentStepNo * m_FrequencyStep;
}

bool WobbulatorForEsp32::isEnabled() const
{
    return enabled;
}

bool WobbulatorForEsp32::isPaused() const
{
    return m_IsPaused;
}

long WobbulatorForEsp32::getStartFrequency() const
{
    return m_Settings->getStartFrequency();
}

long WobbulatorForEsp32::getEndFrequency() const
{
    return m_Settings->getEndFrequency();
}

void WobbulatorForEsp32::setStartFrequency(const long startFrequency)
{
    if ((startFrequency > 0) && (startFrequency < VOBULATOR_MAX_FREQUENCY))
    {
        if (startFrequency < m_Settings->getEndFrequency())
        {
            m_Settings->setStartFrequency(startFrequency);

            m_CurrentStepNo = VOBULATOR_RAMP_FIRST_STEP;

            m_FrequencyStep = (m_Settings->getEndFrequency() - m_Settings->getStartFrequency()) / VOBULATOR_NUMBER_OF_STEPS;
        }
    }
}

void WobbulatorForEsp32::setEndFrequency(const long endFrequency)
{
    if ((endFrequency > 0) && (endFrequency <= VOBULATOR_MAX_FREQUENCY))
    {
        if (m_Settings->getStartFrequency() < endFrequency)
        {
            m_Settings->setEndFrequency(endFrequency);

            m_CurrentStepNo = VOBULATOR_RAMP_FIRST_STEP;

            m_FrequencyStep = (m_Settings->getEndFrequency() - m_Settings->getStartFrequency()) / VOBULATOR_NUMBER_OF_STEPS;
        }
    }
}

#endif