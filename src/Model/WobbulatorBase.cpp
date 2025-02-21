#include "Model/WobbulatorBase.hpp"

#ifdef USE_ESP32

#include <math.h>
#include <stdint.h>
#include <driver/dac.h>

#define VOBULATOR_MAX_FREQUENCY 12500000U
#define VOBULATOR_RAMP_FIRST_STEP 0U
// DAC resolution is 8 bits, so 256 steps
#define VOBULATOR_RAMP_STEP (256 / VOBULATOR_NUMBER_OF_STEPS)

WobbulatorBase *WobbulatorBase::m_Instance = nullptr;

WobbulatorBase *WobbulatorBase::getInstance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new WobbulatorBase();
    }

    return m_Instance;
}

WobbulatorBase::WobbulatorBase()
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

void WobbulatorBase::enable()
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

void WobbulatorBase::disable()
{
    enabled = false;
    m_IsPaused = false;
    dac_output_voltage(DAC_CHANNEL_1, 0U);
    m_Generator->disableWave();
}

void WobbulatorBase::update()
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

void WobbulatorBase::setGenerator(GeneratorIf *generator)
{
    m_Generator = generator;
}

void WobbulatorBase::setsSettingsStorage(SettingsIf *settingsStorage)
{
    m_Settings = settingsStorage;
}

void WobbulatorBase::onRunCallback()
{
    m_Instance->update();
}

void WobbulatorBase::pause()
{
    m_IsPaused = true;
}

void WobbulatorBase::resume()
{
    m_IsPaused = false;
}

void WobbulatorBase::stepUp()
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

void WobbulatorBase::stepDown()
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

long WobbulatorBase::getCurrentFrequency() const
{
    return m_Settings->getStartFrequency() + m_CurrentStepNo * m_FrequencyStep;
}

bool WobbulatorBase::isEnabled() const
{
    return enabled;
}

bool WobbulatorBase::isPaused() const
{
    return m_IsPaused;
}

long WobbulatorBase::getStartFrequency() const
{
    return m_Settings->getStartFrequency();
}

long WobbulatorBase::getEndFrequency() const
{
    return m_Settings->getEndFrequency();
}

void WobbulatorBase::setStartFrequency(const long startFrequency)
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

void WobbulatorBase::setEndFrequency(const long endFrequency)
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