#include "Model/Vobulator.hpp"
#include "ModuleConfig.hpp"

Vobulator *Vobulator::m_Instance = nullptr;

Vobulator *Vobulator::getInstance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new Vobulator();
    }

    return m_Instance;
}

Vobulator::Vobulator()
{
    setInterval(VOBULATOR_THREAD_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;
}

void Vobulator::enable()
{
    enabled = true;
}

void Vobulator::disable()
{
    enabled = false;
}

void Vobulator::update()
{
}

void Vobulator::onRunCallback()
{
    m_Instance->update();
}
