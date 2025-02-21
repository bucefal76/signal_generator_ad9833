#include "Model/Wobbulator.hpp"

#include <math.h>
#include <stdint.h>

#define VOBULATOR_MAX_FREQUENCY 12500000U
#define VOBULATOR_RAMP_FIRST_STEP 0U
// DAC resolution is 8 bits, so 256 steps
#define VOBULATOR_RAMP_STEP (256 / VOBULATOR_NUMBER_OF_STEPS)

Wobbulator *Wobbulator::m_Instance = nullptr;

Wobbulator *Wobbulator::getInstance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new Wobbulator();
    }

    return m_Instance;
}

Wobbulator::Wobbulator()
    : m_Generator(nullptr),
      m_Settings(nullptr),
      m_RampSignalSource(nullptr),
      m_FrequencyStep(1U),
      m_CurrentStepNo(VOBULATOR_RAMP_FIRST_STEP),
      m_IsPaused(false)
{
    setInterval(VOBULATOR_THREAD_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;
}

void Wobbulator::enable()
{
    if (m_Generator != nullptr)
    {
        m_RampSignalSource->setValue(0U);

        m_Generator->disableWave();

        m_CurrentStepNo = VOBULATOR_RAMP_FIRST_STEP;

        m_FrequencyStep = (m_Settings->getEndFrequency() - m_Settings->getStartFrequency()) / VOBULATOR_NUMBER_OF_STEPS;

        m_IsPaused = false;
        enabled = true;
    }
}

void Wobbulator::disable()
{
    enabled = false;
    m_IsPaused = false;
    m_RampSignalSource->setValue(0U);
    m_Generator->disableWave();
}

void Wobbulator::update()
{
    if (enabled && m_Generator != nullptr)
    {
        if (m_CurrentStepNo < VOBULATOR_NUMBER_OF_STEPS)
        {
            const uint8_t rampDcValue = m_CurrentStepNo * VOBULATOR_RAMP_STEP;
            m_RampSignalSource->setValue(rampDcValue);

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

void Wobbulator::setGenerator(GeneratorIf *generator)
{
    m_Generator = generator;
}

void Wobbulator::setSettingsStorage(SettingsIf *settingsStorage)
{
    m_Settings = settingsStorage;
}

void Wobbulator::setRampSignal(RampSignalIf *rampSignalSource)
{
    m_RampSignalSource = rampSignalSource;
}

void Wobbulator::onRunCallback()
{
    m_Instance->update();
}

void Wobbulator::pause()
{
    m_IsPaused = true;
}

void Wobbulator::resume()
{
    m_IsPaused = false;
}

void Wobbulator::stepUp()
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

void Wobbulator::stepDown()
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

long Wobbulator::getCurrentFrequency() const
{
    return m_Settings->getStartFrequency() + m_CurrentStepNo * m_FrequencyStep;
}

bool Wobbulator::isEnabled() const
{
    return enabled;
}

bool Wobbulator::isPaused() const
{
    return m_IsPaused;
}

long Wobbulator::getStartFrequency() const
{
    return m_Settings->getStartFrequency();
}

long Wobbulator::getEndFrequency() const
{
    return m_Settings->getEndFrequency();
}

void Wobbulator::setStartFrequency(const long startFrequency)
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

void Wobbulator::setEndFrequency(const long endFrequency)
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