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
      m_generatorChannel2(nullptr)
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
#ifdef USE_SERIAL

    switch (m_menuState)
    {
    case MenuStateStart:
    {
        if (Serial.available() > 0)
        {
            Serial.read();
            m_menuState = MenuStateMain;
            displayMainMenu();
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
                displayChannelStatus(1, m_generatorChannel1->isEnabled(), m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
                displayChannelMenu();
                break;
            case '2':
                m_menuState = MenuStateChannel2Menu;
                displayChannelStatus(2, m_generatorChannel2->isEnabled(), m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
                displayChannelMenu();
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
                setGenerator1LineWave(m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
                displayChannelStatus(1, m_generatorChannel1->isEnabled(), m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
                displayChannelMenu();
                break;
            case '2':
                disableGeneratorChannel1();
                displayChannelStatus(1, m_generatorChannel1->isEnabled(), m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
                displayChannelMenu();
                break;
            case '3':
                m_menuState = MenuStateChannel1SelectWaveTypeMenu;
                displayChannelStatus(1, m_generatorChannel1->isEnabled(), m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
                displayWaveTypeMenu();
                break;
            case '4':
                m_menuState = MenuStateChannel1SelectFrequencyMenu;
                displayChannelStatus(1, m_generatorChannel1->isEnabled(), m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
                displayFrequencyMenu();
                break;
            default:
                m_menuState = MenuStateMain;
                displayMainMenu();
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
                setGenerator1LineWave(GeneratorIf::TypeSinusoidal, m_lastSelectedGeneratorChannel1Frequency);
                displayChannelStatus(1, m_generatorChannel1->isEnabled(), m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
                displayChannelMenu();
                m_menuState = MenuStateChannel1Menu;
                break;

            case '2':
            {
                setGenerator1LineWave(GeneratorIf::TypeSquare, m_lastSelectedGeneratorChannel1Frequency);
                displayChannelStatus(1, m_generatorChannel1->isEnabled(), m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
                displayChannelMenu();
                m_menuState = MenuStateChannel1Menu;
                break;
            }
            case '3':
            {
                setGenerator1LineWave(GeneratorIf::TypeRamp, m_lastSelectedGeneratorChannel1Frequency);
                displayChannelStatus(1, m_generatorChannel1->isEnabled(), m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
                displayChannelMenu();
                m_menuState = MenuStateChannel1Menu;
                break;
            }
            default:
                setGenerator1LineWave(m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
                m_menuState = MenuStateChannel1Menu;
                displayChannelStatus(1, m_generatorChannel1->isEnabled(), m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
                displayMainMenu();
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
                setGenerator1LineWave(m_lastSelectedGeneratorChannel1WaveType, frequency);
                displayChannelStatus(1, m_generatorChannel1->isEnabled(), m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
                displayChannelMenu();
                m_menuState = MenuStateChannel1Menu;
            }
            else
            {
                m_menuState = MenuStateChannel1Menu;
                Serial.println(F("Invalid frequency!"));
                displayChannelStatus(1, m_generatorChannel1->isEnabled(), m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
                displayMainMenu();
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
                setGenerator2LineWave(m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
                displayChannelStatus(2, m_generatorChannel2->isEnabled(), m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
                displayChannelMenu();
                break;
            case '2':
                disableGeneratorChannel2();
                displayChannelStatus(2, m_generatorChannel2->isEnabled(), m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
                displayChannelMenu();
                break;
            case '3':
                m_menuState = MenuStateChannel2SelectWaveTypeMenu;
                displayChannelStatus(2, m_generatorChannel2->isEnabled(), m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
                displayWaveTypeMenu();
                break;
            case '4':
                m_menuState = MenuStateChannel2SelectFrequencyMenu;
                displayChannelStatus(2, m_generatorChannel2->isEnabled(), m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
                displayFrequencyMenu();
                break;
            default:
                m_menuState = MenuStateMain;
                displayMainMenu();
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
                setGenerator2LineWave(GeneratorIf::TypeSinusoidal, m_lastSelectedGeneratorChannel2Frequency);
                displayChannelStatus(2, m_generatorChannel2->isEnabled(), m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
                displayChannelMenu();
                m_menuState = MenuStateChannel2Menu;
                break;

            case '2':
            {
                setGenerator2LineWave(GeneratorIf::TypeSquare, m_lastSelectedGeneratorChannel2Frequency);
                displayChannelStatus(2, m_generatorChannel2->isEnabled(), m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
                displayChannelMenu();
                m_menuState = MenuStateChannel2Menu;
                break;
            }
            case '3':
            {
                setGenerator2LineWave(GeneratorIf::TypeRamp, m_lastSelectedGeneratorChannel2Frequency);
                displayChannelStatus(2, m_generatorChannel2->isEnabled(), m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
                displayChannelMenu();
                m_menuState = MenuStateChannel2Menu;
                break;
            }
            default:
                setGenerator2LineWave(m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
                m_menuState = MenuStateChannel2Menu;
                displayChannelStatus(2, m_generatorChannel2->isEnabled(), m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
                displayMainMenu();
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
                setGenerator2LineWave(m_lastSelectedGeneratorChannel2WaveType, frequency);
                displayChannelStatus(2, m_generatorChannel2->isEnabled(), m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
                displayChannelMenu();
                m_menuState = MenuStateChannel2Menu;
            }
            else
            {
                m_menuState = MenuStateChannel2Menu;
                Serial.println(F("Invalid frequency!"));
                displayChannelStatus(2, m_generatorChannel2->isEnabled(), m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
                displayMainMenu();
            }
        }

        break;
    }

    default:
        break;
    }

#endif
}

void SerialPortMenu::displayFrequencyMenu()
{
    Serial.print(F("Enter frequency in Hz:"));
}

void SerialPortMenu::onRunCallback()
{
    m_Instance->update();
}

void SerialPortMenu::setGeneratorsToControl(GeneratorIf *generatorLine1, GeneratorIf *generatorLine2)
{
    m_generatorChannel1 = generatorLine1;
    setGenerator1LineWave(GeneratorIf::TypeSquare, DEFAULT_FREQUENCY);

    m_generatorChannel2 = generatorLine2;
    setGenerator2LineWave(GeneratorIf::TypeSquare, DEFAULT_FREQUENCY / 2);
}

void SerialPortMenu::setGenerator1LineWave(const GeneratorIf::WaveType waveType, const long frequency)
{
    if (m_generatorChannel1 != nullptr)
    {
        m_generatorChannel1->generateWave(waveType, frequency);
        m_lastSelectedGeneratorChannel1Frequency = m_generatorChannel1->getFrequency();
        m_lastSelectedGeneratorChannel1WaveType = m_generatorChannel1->getWaveType();
    }
}

void SerialPortMenu::setGenerator2LineWave(const GeneratorIf::WaveType waveType, const long frequency)
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

void SerialPortMenu::displayMainMenu()
{
    Serial.println(F(""));
    Serial.println(F("Signal generator AD9833 control menu:"));
    displayChannelStatus(1, m_generatorChannel1->isEnabled(), m_lastSelectedGeneratorChannel1WaveType, m_lastSelectedGeneratorChannel1Frequency);
    displayChannelStatus(2, m_generatorChannel2->isEnabled(), m_lastSelectedGeneratorChannel2WaveType, m_lastSelectedGeneratorChannel2Frequency);
    Serial.println(F("1 - Set up generator channel 1"));
    Serial.println(F("2 - Set up generator channel 2"));
}

void SerialPortMenu::displayChannelMenu()
{
    Serial.println(F("1 Enable"));
    Serial.println(F("2 Disable"));
    Serial.println(F("3 Select type of signal"));
    Serial.println(F("4 Select frequency"));
    Serial.println(F("0 Return to main menu"));
}

void SerialPortMenu::displayWaveTypeMenu()
{
    Serial.println(F("1 Sinusoidal"));
    Serial.println(F("2 Square"));
    Serial.println(F("3 Ramp"));
    Serial.println(F("0 Return to main menu"));
}

void SerialPortMenu::displayChannelStatus(const uint8_t channelId, const bool channelEnabled, const GeneratorIf::WaveType waveType, const long frequency)
{
    Serial.print(F("Channel "));
    Serial.print(channelId);
    Serial.print(F(": [State: "));
    if (channelEnabled)
    {
        Serial.print(F("Enabled, "));
    }
    else
    {
        Serial.print(F("Disabled, "));
    }
    Serial.print(F("Wave type: "));
    switch (waveType)
    {
    case GeneratorIf::TypeSinusoidal:
        Serial.print(F("Sinusoidal"));
        break;
    case GeneratorIf::TypeSquare:
        Serial.print(F("Square"));
        break;
    case GeneratorIf::TypeRamp:
        Serial.print(F("Ramp"));
        break;
    default:
        Serial.print(F("None"));
        break;
    }
    Serial.print(F(", Frequency: "));
    Serial.print(frequency);
    Serial.println(F(" Hz]"));
}

#endif