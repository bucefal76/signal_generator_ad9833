#include "ModuleConfig.hpp"

#ifdef USE_SERIAL

#include "Controler/SerialPortMenu.hpp"

SerialPortMenu *SerialPortMenu::m_Instance = nullptr;

#define GENERATOR_DEFAULT_FREQUENCY_HZ 1000
#define VOBULATOR_START_FREQUENCY_HZ 20
#define VOBULATOR_END_FREQUENCY_HZ 20000

SerialPortMenu *SerialPortMenu::getInstance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new SerialPortMenu();
    }

    return m_Instance;
}

SerialPortMenu::SerialPortMenu()
    : m_menuState(MenuStateStart),
      m_vobulatorStartFrequency(1),
      m_vobulatorEndFrequency(1),
      m_generatorChannel1(nullptr),
      m_generatorChannel2(nullptr),
      m_view(nullptr),
      m_vobulator(nullptr)
{
    setInterval(SERIAL_MENU_THREAD_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = true;
}

void SerialPortMenu::enable()
{
    enabled = true;
}

void SerialPortMenu::disable()
{
    enabled = false;
}

void SerialPortMenu::update()
{

    if (m_view == nullptr)
    {
        return;
    }

    switch (m_menuState)
    {
    case MenuStateStart:
    {
        if (Serial.available() > 0)
        {
            Serial.read();
            m_menuState = MenuStateMain;
            m_view->displayMainMenu(m_generatorChannel1, m_generatorChannel2);
        }
        break;
    }

    case MenuStateMain:
    {
        if (Serial.available() > 0)
        {
            const char incomingChar = Serial.read();

            switch (incomingChar)
            {
            case '1':
                m_menuState = MenuStateChannel1Menu;
                m_view->displayChannelMenu(m_generatorChannel1);
                break;
            case '2':
                m_menuState = MenuStateChannel2Menu;
                m_view->displayChannelMenu(m_generatorChannel2);
                break;
            case '3':
                Serial.println(F("3"));
                m_menuState = MenuStateVobulatorMenu;
                m_view->displayVobulatorMenu();
                break;
            default:
                break;
            }
        }
        break;
    }

    case MenuStateChannel1Menu:
    {
        if (Serial.available() > 0)
        {
            const char incomingChar = Serial.read();

            switch (incomingChar)
            {
            case '1':
                setGeneratorChannel1Wave(m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
                m_view->displayChannelMenu(m_generatorChannel1);
                break;
            case '2':
                disableGeneratorChannel1();
                m_view->displayChannelMenu(m_generatorChannel1);
                break;
            case '3':
                m_menuState = MenuStateChannel1SelectWaveTypeMenu;
                m_view->displayWaveTypeMenu(m_generatorChannel1);
                break;
            case '4':
                m_menuState = MenuStateChannel1SelectFrequencyMenu;
                m_view->displayFrequencyMenu(m_generatorChannel1);
                break;
            default:
                m_menuState = MenuStateMain;
                m_view->displayMainMenu(m_generatorChannel1, m_generatorChannel2);
                break;
            }
        }
        break;
    }

    case MenuStateChannel1SelectWaveTypeMenu:
    {
        if (Serial.available() > 0)
        {
            const char incomingChar = Serial.read();

            switch (incomingChar)
            {
            case '1':
                setGeneratorChannel1Wave(GeneratorIf::TypeSinusoidal, m_lastSelectedGeneratorChannel1Frequency);
                m_view->displayChannelMenu(m_generatorChannel1);
                m_menuState = MenuStateChannel1Menu;
                break;

            case '2':
            {
                setGeneratorChannel1Wave(GeneratorIf::TypeSquare, m_lastSelectedGeneratorChannel1Frequency);
                m_view->displayChannelMenu(m_generatorChannel1);
                m_menuState = MenuStateChannel1Menu;
                break;
            }
            case '3':
            {
                setGeneratorChannel1Wave(GeneratorIf::TypeRamp, m_lastSelectedGeneratorChannel1Frequency);
                m_view->displayChannelMenu(m_generatorChannel1);
                m_menuState = MenuStateChannel1Menu;
                break;
            }
            default:
                setGeneratorChannel1Wave(m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
                m_menuState = MenuStateChannel1Menu;
                m_view->displayMainMenu(m_generatorChannel1, m_generatorChannel2);
                break;
            }
        }

        break;
    }

    case MenuStateChannel1SelectFrequencyMenu:
    {
        if (Serial.available() > 0)
        {
            const String input = Serial.readString();
            Serial.println(input);

            const long frequency = atol(input.c_str());

            if (frequency > 0)
            {
                setGeneratorChannel1Wave(m_lastSelectedGeneratorChannel1WaveType, frequency);
                m_view->displayChannelMenu(m_generatorChannel1);
                m_menuState = MenuStateChannel1Menu;
            }
            else
            {
                m_menuState = MenuStateChannel1Menu;
                Serial.println(F("Invalid frequency!"));
                m_view->displayMainMenu(m_generatorChannel1, m_generatorChannel2);
            }
        }

        break;
    }

    case MenuStateChannel2Menu:
    {
        if (Serial.available() > 0)
        {
            const char incomingChar = Serial.read();

            switch (incomingChar)
            {
            case '1':
                setGeneratorChannel2Wave(m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
                m_view->displayChannelMenu(m_generatorChannel2);
                break;
            case '2':
                disableGeneratorChannel2();
                m_view->displayChannelMenu(m_generatorChannel2);
                break;
            case '3':
                m_menuState = MenuStateChannel2SelectWaveTypeMenu;
                m_view->displayWaveTypeMenu(m_generatorChannel2);
                break;
            case '4':
                m_menuState = MenuStateChannel2SelectFrequencyMenu;
                m_view->displayFrequencyMenu(m_generatorChannel2);
                break;
            default:
                m_menuState = MenuStateMain;
                m_view->displayMainMenu(m_generatorChannel1, m_generatorChannel2);
                break;
            }
        }
        break;
    }

    case MenuStateChannel2SelectWaveTypeMenu:
    {
        if (Serial.available() > 0)
        {
            const char incomingChar = Serial.read();

            switch (incomingChar)
            {
            case '1':
                setGeneratorChannel2Wave(GeneratorIf::TypeSinusoidal, m_lastSelectedGeneratorChannel2Frequency);
                m_view->displayChannelMenu(m_generatorChannel2);
                m_menuState = MenuStateChannel2Menu;
                break;

            case '2':
            {
                setGeneratorChannel2Wave(GeneratorIf::TypeSquare, m_lastSelectedGeneratorChannel2Frequency);
                m_view->displayChannelMenu(m_generatorChannel2);
                m_menuState = MenuStateChannel2Menu;
                break;
            }
            case '3':
            {
                setGeneratorChannel2Wave(GeneratorIf::TypeRamp, m_lastSelectedGeneratorChannel2Frequency);
                m_view->displayChannelMenu(m_generatorChannel2);
                m_menuState = MenuStateChannel2Menu;
                break;
            }
            default:
                setGeneratorChannel2Wave(m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
                m_menuState = MenuStateChannel2Menu;
                m_view->displayMainMenu(m_generatorChannel1,m_generatorChannel2);
                break;
            }
        }

        break;
    }

    case MenuStateChannel2SelectFrequencyMenu:
    {
        if (Serial.available() > 0)
        {
            const String input = Serial.readString();
            Serial.println(input);

            const long frequency = atol(input.c_str());

            if (frequency > 0)
            {
                setGeneratorChannel2Wave(m_lastSelectedGeneratorChannel2WaveType, frequency);
                m_view->displayChannelMenu(m_generatorChannel1);
                m_menuState = MenuStateChannel2Menu;
            }
            else
            {
                m_menuState = MenuStateChannel2Menu;
                Serial.println(F("Invalid frequency!"));
                m_view->displayMainMenu(m_generatorChannel1, m_generatorChannel2);
            }
        }

        break;
    }

    case MenuStateVobulatorMenu:
    {
        if (Serial.available() > 0)
        {
            const char incomingChar = Serial.read();

            switch (incomingChar)
            {
            case '1':
                enableVobulator();
                break;
            case '2':
                disableVobulator();
                break;
            case '3':
                pauseVobulator();
                break;
            case '4':
                resumeVobulator();
                break;
            case '5':
                stepUpVobulator();
                break;
            case '6':
                stepDownVobulator();
                break;
            default:
                m_view->displayMainMenu(nullptr, nullptr);
                m_menuState = MenuStateMain;
                break;
            }
        }
    }

    default:
        break;
    }
}

void SerialPortMenu::onRunCallback()
{
    m_Instance->update();
}

void SerialPortMenu::setGeneratorsToControl(GeneratorIf *generatorLine1, GeneratorIf *generatorLine2)
{
    m_generatorChannel1 = generatorLine1;
    setGeneratorChannel1Wave(GeneratorIf::TypeSquare, GENERATOR_DEFAULT_FREQUENCY_HZ);
    /// setGeneratorChannel1Wave(GeneratorIf::TypeSquare, 1000000);

    m_generatorChannel2 = generatorLine2;
    setGeneratorChannel2Wave(GeneratorIf::TypeSquare, GENERATOR_DEFAULT_FREQUENCY_HZ / 2);
    /// setGeneratorChannel2Wave(GeneratorIf::TypeSinusoidal, 1000000);
}

void SerialPortMenu::setView(ViewIf *view)
{
    m_view = view;
}

void SerialPortMenu::setVobulator(VobulatorIf *vobulator)
{
    m_vobulator = vobulator;
}

void SerialPortMenu::setGeneratorChannel1Wave(const GeneratorIf::WaveType waveType, const long frequency)
{
    if (m_generatorChannel1 != nullptr)
    {
        m_generatorChannel1->generateWave(waveType, frequency);
        m_lastSelectedGeneratorChannel1Frequency = m_generatorChannel1->getFrequency();
        m_lastSelectedGeneratorChannel1WaveType = m_generatorChannel1->getWaveType();
    }
}

void SerialPortMenu::setGeneratorChannel2Wave(const GeneratorIf::WaveType waveType, const long frequency)
{
    if (m_generatorChannel2 != nullptr)
    {
        m_generatorChannel2->generateWave(waveType, frequency);
        m_lastSelectedGeneratorChannel2Frequency = m_generatorChannel2->getFrequency();
        m_lastSelectedGeneratorChannel2WaveType = m_generatorChannel2->getWaveType();
    }
}

void SerialPortMenu::disableGeneratorChannel1()
{
    if (m_generatorChannel1 != nullptr)
    {
        m_generatorChannel1->disableWave();
    }
}

void SerialPortMenu::disableGeneratorChannel2()
{
    if (m_generatorChannel2 != nullptr)
    {
        m_generatorChannel2->disableWave();
    }
}

void SerialPortMenu::enableVobulator()
{
    if (m_vobulator != nullptr)
    {
        setGeneratorChannel1Wave(GeneratorIf::TypeNone, GENERATOR_DEFAULT_FREQUENCY_HZ);
        setGeneratorChannel2Wave(GeneratorIf::TypeNone, GENERATOR_DEFAULT_FREQUENCY_HZ);
        m_vobulator->enable();
    }
}
void SerialPortMenu::disableVobulator()
{
    if (m_vobulator != nullptr)
    {
        m_vobulator->disable();
    }
}

void SerialPortMenu::pauseVobulator()
{
    if (m_vobulator != nullptr)
    {
        m_vobulator->pause();
    }
}

void SerialPortMenu::resumeVobulator()
{
    if (m_vobulator != nullptr)
    {
        m_vobulator->resume();
    }
}

void SerialPortMenu::stepUpVobulator()
{
    if (m_vobulator != nullptr)
    {
        m_vobulator->stepUp();
    }
}

void SerialPortMenu::stepDownVobulator()
{
    if (m_vobulator != nullptr)
    {
        m_vobulator->stepDown();
    }
}

#endif