#include "ModuleConfig.hpp"

#ifdef USE_SERIAL

#include "Controler/SerialPortMenu.hpp"

SerialPortMenu *SerialPortMenu::m_Instance = nullptr;

#define DEFAULT_FREQUENCY 1000

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
      m_generatorChannel1(nullptr),
      m_generatorChannel2(nullptr),
      m_view(nullptr)
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
            displayChannel1Status();
            if (m_generatorChannel2 != nullptr)
            {
                m_view->displayChannelStatus(2, m_generatorChannel2->isEnabled(), m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
            }
            m_view->displayMainMenu();
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
                displayChannel1Status();
                m_view->displayChannelMenu();
                break;
            case '2':
                m_menuState = MenuStateChannel2Menu;
                if (m_generatorChannel2 != nullptr)
                {
                    m_view->displayChannelStatus(2, m_generatorChannel2->isEnabled(), m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
                }
                m_view->displayChannelMenu();
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
                displayChannel1Status();
                m_view->displayChannelMenu();
                break;
            case '2':
                disableGeneratorChannel1();
                displayChannel1Status();
                m_view->displayChannelMenu();
                break;
            case '3':
                m_menuState = MenuStateChannel1SelectWaveTypeMenu;
                displayChannel1Status();
                m_view->displayWaveTypeMenu();
                break;
            case '4':
                m_menuState = MenuStateChannel1SelectFrequencyMenu;
                displayChannel1Status();
                m_view->displayFrequencyMenu();
                break;
            default:
                m_menuState = MenuStateMain;
                displayChannel1Status();
                displayChannel2Status();
                m_view->displayMainMenu();
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
                displayChannel1Status();
                m_view->displayChannelMenu();
                m_menuState = MenuStateChannel1Menu;
                break;

            case '2':
            {
                setGeneratorChannel1Wave(GeneratorIf::TypeSquare, m_lastSelectedGeneratorChannel1Frequency);
                displayChannel1Status();
                m_view->displayChannelMenu();
                m_menuState = MenuStateChannel1Menu;
                break;
            }
            case '3':
            {
                setGeneratorChannel1Wave(GeneratorIf::TypeRamp, m_lastSelectedGeneratorChannel1Frequency);
                displayChannel1Status();
                m_view->displayChannelMenu();
                m_menuState = MenuStateChannel1Menu;
                break;
            }
            default:
                setGeneratorChannel1Wave(m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
                m_menuState = MenuStateChannel1Menu;
                displayChannel1Status();
                m_view->displayMainMenu();
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
                displayChannel1Status();
                m_view->displayChannelMenu();
                m_menuState = MenuStateChannel1Menu;
            }
            else
            {
                m_menuState = MenuStateChannel1Menu;
                Serial.println(F("Invalid frequency!"));
                displayChannel1Status();
                m_view->displayMainMenu();
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
                displayChannel2Status();
                m_view->displayChannelMenu();
                break;
            case '2':
                disableGeneratorChannel2();
                displayChannel2Status();
                m_view->displayChannelMenu();
                break;
            case '3':
                m_menuState = MenuStateChannel2SelectWaveTypeMenu;
                displayChannel2Status();
                m_view->displayWaveTypeMenu();
                break;
            case '4':
                m_menuState = MenuStateChannel2SelectFrequencyMenu;
                displayChannel2Status();
                m_view->displayFrequencyMenu();
                break;
            default:
                m_menuState = MenuStateMain;
                displayChannel1Status();
                displayChannel2Status();
                m_view->displayMainMenu();
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
                displayChannel2Status();
                m_view->displayChannelMenu();
                m_menuState = MenuStateChannel2Menu;
                break;

            case '2':
            {
                setGeneratorChannel2Wave(GeneratorIf::TypeSquare, m_lastSelectedGeneratorChannel2Frequency);
                displayChannel2Status();
                m_view->displayChannelMenu();
                m_menuState = MenuStateChannel2Menu;
                break;
            }
            case '3':
            {
                setGeneratorChannel2Wave(GeneratorIf::TypeRamp, m_lastSelectedGeneratorChannel2Frequency);
                displayChannel2Status();
                m_view->displayChannelMenu();
                m_menuState = MenuStateChannel2Menu;
                break;
            }
            default:
                setGeneratorChannel2Wave(m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
                m_menuState = MenuStateChannel2Menu;
                displayChannel2Status();
                m_view->displayMainMenu();
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
                displayChannel2Status();
                m_view->displayChannelMenu();
                m_menuState = MenuStateChannel2Menu;
            }
            else
            {
                m_menuState = MenuStateChannel2Menu;
                Serial.println(F("Invalid frequency!"));
                displayChannel2Status();
                m_view->displayMainMenu();
            }
        }

        break;
    }

    default:
        break;
    }
}

void SerialPortMenu::onRunCallback()
{
    m_Instance->update();
}

void SerialPortMenu::displayChannel1Status()
{
    if (m_generatorChannel1 != nullptr)
    {
        m_view->displayChannelStatus(1, m_generatorChannel1->isEnabled(), m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
    }
}

void SerialPortMenu::displayChannel2Status()
{
    if (m_generatorChannel2 != nullptr)
    {
        m_view->displayChannelStatus(2, m_generatorChannel2->isEnabled(), m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
    }
}

void SerialPortMenu::setGeneratorsToControl(GeneratorIf *generatorLine1, GeneratorIf *generatorLine2)
{
    m_generatorChannel1 = generatorLine1;
    setGeneratorChannel1Wave(GeneratorIf::TypeSquare, DEFAULT_FREQUENCY);
    /// setGeneratorChannel1Wave(GeneratorIf::TypeSquare, 1000000);

    m_generatorChannel2 = generatorLine2;
    setGeneratorChannel2Wave(GeneratorIf::TypeSquare, DEFAULT_FREQUENCY / 2);
    /// setGeneratorChannel2Wave(GeneratorIf::TypeSinusoidal, 1000000);
}

void SerialPortMenu::setView(ViewIf *view)
{
    m_view = view;
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

#endif