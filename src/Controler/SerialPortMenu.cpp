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
    if (Serial.available() > 0)
    {
        Serial.println(F("Menu:"));
        Serial.println(F("1 - Enable/disable generator LINE 1"));
        Serial.println(F("2 - Enable/disable generator LINE 2"));
        Serial.println(F("3 - Enable/disable vobulator LINE 1"));

        char incomingChar = Serial.read();
    }
#endif
}

void SerialPortMenu::onRunCallback()
{
    m_Instance->update();
}
