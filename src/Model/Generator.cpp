#include "Model/Generator.hpp"

#include "AD9833.h"

Generator::Generator()
    : m_AD(nullptr)
{
    Serial.println(F("Creating AD9833 object."));

    m_AD = new AD9833(10); //  HW SPI, select pin 10

    Serial.println(F("SPI begin."));

    SPI.begin();

    Serial.println(F("AD9833 begin."));

    m_AD->begin();
    m_AD->setFrequency(1000, 0); //  1000 Hz.

    m_AD->setWave(AD9833_SQUARE1);
}