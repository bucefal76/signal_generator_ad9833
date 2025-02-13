#include "Controler/SerialPortMenu.hpp"
#include "ModuleConfig.hpp"

SerialPortMenu *SerialPortMenu::m_Instance = nullptr;

SerialPortMenu *SerialPortMenu::getInstance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new SerialPortMenu();
    }

    return m_Instance;
}

SerialPortMenu::SerialPortMenu()
    : m_menuState(MenuStateStart)
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
                displayChannel1Menu();
                break;
            case '2':
                m_menuState = MenuStateChannel2Menu;
                displayChannel2Menu();
                break;
            case '3':
                m_menuState = MenuStateChannel1VobulatorMenu;
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
                m_menuState = MenuStateChannel1Menu;
                break;
            case '2':
                m_menuState = MenuStateChannel1Menu;
                break;
            default:
                m_menuState = MenuStateMain;
                displayMainMenu();
                break;
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
                m_menuState = MenuStateChannel2Menu;
                break;
            case '2':
                m_menuState = MenuStateChannel2Menu;
                break;
            default:
                m_menuState = MenuStateMain;
                displayMainMenu();
                break;
            }
        }
        break;
    }

    default:
        break;
    }

#endif
}

void SerialPortMenu::displayMainMenu()
{
    Serial.println(F(""));
    Serial.println(F("Main Menu:"));
    Serial.println(F("1 - Enable/disable generator LINE 1"));
    Serial.println(F("2 - Enable/disable generator LINE 2"));
    Serial.println(F("3 - Enable/disable vobulator LINE 1"));
}

void SerialPortMenu::displayChannel1Menu()
{
    Serial.println(F(""));
    Serial.println(F("Channel 1 settings:"));
    Serial.println(F("1 Select type of signal"));
    Serial.println(F("2 Select frequency"));
    Serial.println(F("0 Return to main menu"));
}

void SerialPortMenu::displayChannel2Menu()
{

    Serial.println(F(""));
    Serial.println(F("Channel 2 settings:"));
    Serial.println(F("1 Select type of signal"));
    Serial.println(F("2 Select frequency"));
    Serial.println(F("0 Return to main menu"));
}

void SerialPortMenu::onRunCallback()
{
    m_Instance->update();
}
