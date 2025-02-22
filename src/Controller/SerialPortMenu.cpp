#include "ModuleConfig.hpp"

#ifdef USE_SERIAL

#include "Controler/SerialPortMenu.hpp"

SerialPortMenu *SerialPortMenu::m_Instance = nullptr;

#define GENERATOR_DEFAULT_FREQUENCY_HZ 1000

SerialPortMenu *SerialPortMenu::getInstance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new SerialPortMenu();
    }

    return m_Instance;
}

SerialPortMenu::SerialPortMenu()
    : m_MenuState(MenuStateStart),
      m_GeneratorChannel1(nullptr),
      m_GeneratorChannel2(nullptr),
      m_View(nullptr),
      m_Wobbulator(nullptr),
      m_Settings(nullptr)
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

    if (m_View == nullptr)
    {
        Serial.println("ERROR - SerialPortMenu.m_View is nullptr!!!");
        return;
    }

    if (m_Settings == nullptr)
    {
        Serial.println("ERROR - SerialPortMenu.m_Settings is nullptr!!!");
        return;
    }

    switch (m_MenuState)
    {
    case MenuStateStart:
    {
        if (Serial.available() > 0)
        {
            Serial.read();
            m_MenuState = MenuStateMain;
            m_View->displayMainMenu(m_GeneratorChannel1, m_GeneratorChannel2, m_Wobbulator);
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
                m_MenuState = MenuStateChannel1Menu;
                m_View->displayGeneratorChannelMenu(m_GeneratorChannel1);
                break;
            case '2':
                if (m_GeneratorChannel2 != nullptr)
                {
                    m_MenuState = MenuStateChannel2Menu;
                    m_View->displayGeneratorChannelMenu(m_GeneratorChannel2);
                }
                else
                {
                    m_View->displayMainMenu(m_GeneratorChannel1, m_GeneratorChannel2, m_Wobbulator);
                }
                break;
            case '3':
                if (m_Wobbulator != nullptr)
                {
                    m_MenuState = MenuStateWobbulatorMenu;
                    m_View->displayWobbulatorMenu(m_Wobbulator);
                }
                else
                {
                    m_View->displayMainMenu(m_GeneratorChannel1, m_GeneratorChannel2, m_Wobbulator);
                }
                break;
            default:
                m_View->displayMainMenu(m_GeneratorChannel1, m_GeneratorChannel2, m_Wobbulator);
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
                setGeneratorChannel1Wave(m_Settings->getGenerator1Wave(), m_Settings->getGenerator1Frequency());
                m_View->displayGeneratorChannelMenu(m_GeneratorChannel1);
                break;
            case '2':
                disableGeneratorChannel1();
                m_View->displayGeneratorChannelMenu(m_GeneratorChannel1);
                break;
            case '3':
                m_MenuState = MenuStateChannel1SelectWaveTypeMenu;
                m_View->displayGeneratorWaveTypeSelectionMenu(m_GeneratorChannel1);
                break;
            case '4':
                m_MenuState = MenuStateChannel1SelectFrequencyMenu;
                m_View->displayGeneratorFrequencySelectionMenu(m_GeneratorChannel1);
                break;
            default:
                m_MenuState = MenuStateMain;
                m_View->displayMainMenu(m_GeneratorChannel1, m_GeneratorChannel2, m_Wobbulator);
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
                setGeneratorChannel1Wave(GeneratorIf::TypeSinusoidal, m_Settings->getGenerator1Frequency());
                m_View->displayGeneratorChannelMenu(m_GeneratorChannel1);
                m_MenuState = MenuStateChannel1Menu;
                break;

            case '2':
            {
                setGeneratorChannel1Wave(GeneratorIf::TypeSquare, m_Settings->getGenerator1Frequency());
                m_View->displayGeneratorChannelMenu(m_GeneratorChannel1);
                m_MenuState = MenuStateChannel1Menu;
                break;
            }
            case '3':
            {
                setGeneratorChannel1Wave(GeneratorIf::TypeRamp, m_Settings->getGenerator1Frequency());
                m_View->displayGeneratorChannelMenu(m_GeneratorChannel1);
                m_MenuState = MenuStateChannel1Menu;
                break;
            }
            default:
                setGeneratorChannel1Wave(m_Settings->getGenerator1Wave(), m_Settings->getGenerator1Frequency());
                m_MenuState = MenuStateChannel1Menu;
                m_View->displayMainMenu(m_GeneratorChannel1, m_GeneratorChannel2, m_Wobbulator);
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
                setGeneratorChannel1Wave(m_Settings->getGenerator1Wave(), frequency);
                m_View->displayGeneratorChannelMenu(m_GeneratorChannel1);
                m_MenuState = MenuStateChannel1Menu;
            }
            else
            {
                m_MenuState = MenuStateChannel1Menu;
                Serial.println(F("Invalid frequency!"));
                m_View->displayMainMenu(m_GeneratorChannel1, m_GeneratorChannel2, m_Wobbulator);
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
                setGeneratorChannel2Wave(m_Settings->getGenerator2Wave(), m_Settings->getGenerator2Frequency());
                m_View->displayGeneratorChannelMenu(m_GeneratorChannel2);
                break;
            case '2':
                disableGeneratorChannel2();
                m_View->displayGeneratorChannelMenu(m_GeneratorChannel2);
                break;
            case '3':
                m_MenuState = MenuStateChannel2SelectWaveTypeMenu;
                m_View->displayGeneratorWaveTypeSelectionMenu(m_GeneratorChannel2);
                break;
            case '4':
                m_MenuState = MenuStateChannel2SelectFrequencyMenu;
                m_View->displayGeneratorFrequencySelectionMenu(m_GeneratorChannel2);
                break;
            default:
                m_MenuState = MenuStateMain;
                m_View->displayMainMenu(m_GeneratorChannel1, m_GeneratorChannel2, m_Wobbulator);
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
                setGeneratorChannel2Wave(GeneratorIf::TypeSinusoidal, m_Settings->getGenerator2Frequency());
                m_View->displayGeneratorChannelMenu(m_GeneratorChannel2);
                m_MenuState = MenuStateChannel2Menu;
                break;

            case '2':
            {
                setGeneratorChannel2Wave(GeneratorIf::TypeSquare, m_Settings->getGenerator2Frequency());
                m_View->displayGeneratorChannelMenu(m_GeneratorChannel2);
                m_MenuState = MenuStateChannel2Menu;
                break;
            }
            case '3':
            {
                setGeneratorChannel2Wave(GeneratorIf::TypeRamp, m_Settings->getGenerator2Frequency());
                m_View->displayGeneratorChannelMenu(m_GeneratorChannel2);
                m_MenuState = MenuStateChannel2Menu;
                break;
            }
            default:
                setGeneratorChannel2Wave(m_Settings->getGenerator2Wave(), m_Settings->getGenerator2Frequency());
                m_MenuState = MenuStateChannel2Menu;
                m_View->displayMainMenu(m_GeneratorChannel1, m_GeneratorChannel2, m_Wobbulator);
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
                setGeneratorChannel2Wave(m_Settings->getGenerator2Wave(), frequency);
                m_View->displayGeneratorChannelMenu(m_GeneratorChannel2);
                m_MenuState = MenuStateChannel2Menu;
            }
            else
            {
                m_MenuState = MenuStateChannel2Menu;
                Serial.println(F("Invalid frequency!"));
                m_View->displayMainMenu(m_GeneratorChannel1, m_GeneratorChannel2, m_Wobbulator);
            }
        }

        break;
    }

    case MenuStateWobbulatorMenu:
    {
        if (Serial.available() > 0)
        {
            const char incomingChar = Serial.read();

            switch (incomingChar)
            {
            case '1':
                enableWobbulator();
                m_View->displayWobbulatorMenu(m_Wobbulator);
                break;
            case '2':
                disableWobbulator();
                m_View->displayWobbulatorMenu(m_Wobbulator);
                break;
            case '3':
                pauseWobbulator();
                m_View->displayWobbulatorMenu(m_Wobbulator);
                break;
            case '4':
                resumeWobbulator();
                m_View->displayWobbulatorMenu(m_Wobbulator);
                break;
            case '5':
                stepUpWobbulator();
                m_View->displayWobbulatorMenu(m_Wobbulator);
                break;
            case '6':
                stepDownWobbulator();
                m_View->displayWobbulatorMenu(m_Wobbulator);
                break;
            case '7':
                m_View->displayWobbulatorFrequencySelectionMenu(m_Wobbulator, ViewIf::FrequencyStart);
                m_MenuState = MenuStateWobbulatorSelectStartFrequencyMenu;
                break;
            case '8':
                m_View->displayWobbulatorFrequencySelectionMenu(m_Wobbulator, ViewIf::FrequencyStart);
                m_MenuState = MenuStateWobbulatorSelectEndFrequencyMenu;
                break;
            default:
                m_View->displayMainMenu(m_GeneratorChannel1, m_GeneratorChannel2, m_Wobbulator);
                m_MenuState = MenuStateMain;
                break;
            }
        }

        break;
    }

    case MenuStateWobbulatorSelectStartFrequencyMenu:
    {
        if (Serial.available() > 0)
        {
            const String input = Serial.readString();
            Serial.println(input);

            const long frequency = atol(input.c_str());

            if (frequency > 0)
            {
                setStartFrequencyForWobbulator(frequency);
                m_View->displayWobbulatorMenu(m_Wobbulator);
                m_MenuState = MenuStateWobbulatorMenu;
            }
            else
            {
                Serial.println(F("Invalid frequency!"));
                m_View->displayWobbulatorMenu(m_Wobbulator);
                m_MenuState = MenuStateWobbulatorMenu;
            }
        }

        break;
    }

    case MenuStateWobbulatorSelectEndFrequencyMenu:
    {
        if (Serial.available() > 0)
        {
            const String input = Serial.readString();
            Serial.println(input);

            const long frequency = atol(input.c_str());

            if (frequency > 0)
            {
                setEndFrequencyForWobbulator(frequency);
                m_View->displayWobbulatorMenu(m_Wobbulator);
                m_MenuState = MenuStateWobbulatorMenu;
            }
            else
            {
                Serial.println(F("Invalid frequency!"));
                m_View->displayWobbulatorMenu(m_Wobbulator);
                m_MenuState = MenuStateWobbulatorMenu;
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

void SerialPortMenu::setGeneratorsToControl(GeneratorIf *generatorLine1, GeneratorIf *generatorLine2)
{
    m_GeneratorChannel1 = generatorLine1;
    setGeneratorChannel1Wave(GeneratorIf::TypeSquare, GENERATOR_DEFAULT_FREQUENCY_HZ);
    /// setGeneratorChannel1Wave(GeneratorIf::TypeSquare, 1000000);

    m_GeneratorChannel2 = generatorLine2;
    setGeneratorChannel2Wave(GeneratorIf::TypeSquare, GENERATOR_DEFAULT_FREQUENCY_HZ / 2);
    /// setGeneratorChannel2Wave(GeneratorIf::TypeSinusoidal, 1000000);
}

void SerialPortMenu::setView(ViewIf *view)
{
    m_View = view;
}

void SerialPortMenu::setWobbulator(WobbulatorIf *wobbulator)
{
    m_Wobbulator = wobbulator;
}

void SerialPortMenu::setSettingsStorage(SettingsIf *settingsStorage)
{
    m_Settings = settingsStorage;
}

void SerialPortMenu::setGeneratorChannel1Wave(const GeneratorIf::WaveType waveType, const long frequency)
{
    if (m_GeneratorChannel1 != nullptr)
    {
        // Disable wobbulator if needed
        if (m_Wobbulator != nullptr)
        {
            m_Wobbulator->disable();
        }
        // Now enable generator
        m_GeneratorChannel1->generateWave(waveType, frequency);
        m_Settings->setGenerator1Frequency(m_GeneratorChannel1->getFrequency());
        m_Settings->setGenerator1Wave(m_GeneratorChannel1->getWaveType());
    }
}

void SerialPortMenu::setGeneratorChannel2Wave(const GeneratorIf::WaveType waveType, const long frequency)
{
    if (m_GeneratorChannel2 != nullptr)
    {
        m_GeneratorChannel2->generateWave(waveType, frequency);
        m_Settings->setGenerator2Frequency(m_GeneratorChannel2->getFrequency());
        m_Settings->setGenerator2Wave(m_GeneratorChannel2->getWaveType());
    }
}

void SerialPortMenu::disableGeneratorChannel1()
{
    if (m_GeneratorChannel1 != nullptr)
    {
        // Disable wobbulator if needed
        if (m_Wobbulator != nullptr)
        {
            m_Wobbulator->disable();
        }

        m_GeneratorChannel1->disableWave();
    }
}

void SerialPortMenu::disableGeneratorChannel2()
{
    if (m_GeneratorChannel2 != nullptr)
    {
        m_GeneratorChannel2->disableWave();
    }
}

void SerialPortMenu::enableWobbulator()
{
    if (m_Wobbulator != nullptr)
    {
        if (nullptr != m_GeneratorChannel1)
        {
            /// Do not overwrite the stored in memory generator settings, just turn OFF the generator
            m_GeneratorChannel1->generateWave(GeneratorIf::TypeNone, GENERATOR_DEFAULT_FREQUENCY_HZ);
        }
        if (nullptr != m_GeneratorChannel2)
        {
            /// Do not overwrite the stored in memory generator settings, just turn OFF the generator
            m_GeneratorChannel2->generateWave(GeneratorIf::TypeNone, GENERATOR_DEFAULT_FREQUENCY_HZ);
        }
        m_Wobbulator->enable();
    }
}
void SerialPortMenu::disableWobbulator()
{
    if (m_Wobbulator != nullptr)
    {
        m_Wobbulator->disable();
    }
}

void SerialPortMenu::pauseWobbulator()
{
    if (m_Wobbulator != nullptr)
    {
        m_Wobbulator->pause();
    }
}

void SerialPortMenu::resumeWobbulator()
{
    if (m_Wobbulator != nullptr)
    {
        m_Wobbulator->resume();
    }
}

void SerialPortMenu::stepUpWobbulator()
{
    if (m_Wobbulator != nullptr)
    {
        m_Wobbulator->stepUp();
    }
}

void SerialPortMenu::stepDownWobbulator()
{
    if (m_Wobbulator != nullptr)
    {
        m_Wobbulator->stepDown();
    }
}

void SerialPortMenu::setStartFrequencyForWobbulator(const long frequency)
{
    if (m_Wobbulator != nullptr)
    {
        m_Wobbulator->resume();
        m_Wobbulator->disable();
        m_Wobbulator->setStartFrequency(frequency);
        m_Wobbulator->enable();
    }
}

void SerialPortMenu::setEndFrequencyForWobbulator(const long frequency)
{
    if (m_Wobbulator != nullptr)
    {
        m_Wobbulator->resume();
        m_Wobbulator->disable();
        m_Wobbulator->setEndFrequency(frequency);
        m_Wobbulator->enable();
    }
}

#endif