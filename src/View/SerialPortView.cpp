#include "View/SerialPortView.hpp"

#ifdef USE_SERIAL

void SerialPortView::displayMainMenu(const GeneratorIf *generator1, const GeneratorIf *generator2, const WobbulatorIf *wobbulator) const
{
    if (wobbulator != nullptr)
    {
        displayWobbulatorStatus(wobbulator->isEnabled(),
                                wobbulator->isPaused(),
                                wobbulator->getCurrentFrequency(),
                                wobbulator->getStartFrequency(),
                                wobbulator->getEndFrequency());
    }
    if (generator1 != nullptr)
    {
        displayChannelStatus(generator1->getChannelId(), generator1->isEnabled(), generator1->getWaveType(), generator1->getFrequency());
    }
    if (generator2 != nullptr)
    {
        displayChannelStatus(generator2->getChannelId(), generator2->isEnabled(), generator2->getWaveType(), generator2->getFrequency());
    }

    Serial.println(F("Main menu:"));

    if (generator1 != nullptr)
    {
        Serial.println(F("1. Channel 1"));
    }
    if (generator2 != nullptr)
    {
        Serial.println(F("2. Channel 2"));
    }
    if (wobbulator != nullptr)
    {
        Serial.println(F("3. Wobbulator - channel 1"));
    }
}

void SerialPortView::displayGeneratorChannelMenu(const GeneratorIf *generator) const
{
    if (generator != nullptr)
    {
        displayChannelStatus(generator->getChannelId(), generator->isEnabled(), generator->getWaveType(), generator->getFrequency());
    }
    Serial.println(F("Channel menu:"));
    Serial.println(F("1. Enable"));
    Serial.println(F("2. Disable"));
    Serial.println(F("3. Select wave type"));
    Serial.println(F("4. Select frequency"));
    Serial.println(F("0. Return to main menu"));
}

void SerialPortView::displayGeneratorWaveTypeSelectionMenu(const GeneratorIf *generator) const
{
    if (generator != nullptr)
    {
        displayChannelStatus(generator->getChannelId(), generator->isEnabled(), generator->getWaveType(), generator->getFrequency());
    }
    Serial.println(F("Wave type menu:"));
    Serial.println(F("1. Sinusoidal"));
    Serial.println(F("2. Square"));
    Serial.println(F("3. Ramp"));
    Serial.println(F("0. Return to channel menu"));
}

void SerialPortView::displayGeneratorFrequencySelectionMenu(const GeneratorIf *generator) const
{
    if (generator != nullptr)
    {
        displayChannelStatus(generator->getChannelId(), generator->isEnabled(), generator->getWaveType(), generator->getFrequency());
    }
    Serial.println(F("Frequency menu:"));
    Serial.println(F("Enter frequency in Hz:"));
}

void SerialPortView::displayChannelStatus(const uint8_t channelId, const bool channelEnabled, const GeneratorIf::WaveType waveType, const long frequency) const
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

void SerialPortView::displayWobbulatorMenu(const WobbulatorIf *wobbulator) const
{
    if (wobbulator != nullptr)
    {
        displayWobbulatorStatus(wobbulator->isEnabled(),
                                wobbulator->isPaused(),
                                wobbulator->getCurrentFrequency(),
                                wobbulator->getStartFrequency(),
                                wobbulator->getEndFrequency());
    }

    Serial.println(F("Wobbulator menu:"));
    Serial.println(F("1. Enable"));
    Serial.println(F("2. Disable"));
    Serial.println(F("3. Pause"));
    Serial.println(F("4. Resume"));
    Serial.println(F("5. Step up"));
    Serial.println(F("6. Step down"));
    Serial.println(F("7. Set start frequency"));
    Serial.println(F("8. Set end frequency"));
    Serial.println(F("0. Return to main menu"));
}

void SerialPortView::displayWobbulatorStatus(const bool isEnabled,
                                             const bool isPaused,
                                             const long currentFrequency,
                                             const long startFrequency,
                                             const long endFrequency) const
{
    Serial.print(F("Wobbulator"));
    Serial.print(F(": [State: "));
    if (isEnabled)

    {
        Serial.print(F("Enabled, "));
        if (isPaused)
        {
            Serial.print(F("Paused, "));
            Serial.print(F("Current frequency: "));
            Serial.print(currentFrequency);
            Serial.println(F(" Hz]"));
        }
        else
        {
            Serial.print(F("Auto, Start: "));
            Serial.print(startFrequency);
            Serial.print(F(" Hz, End: "));
            Serial.print(endFrequency);
            Serial.println(F(" Hz]"));
        }
    }
    else
    {
        Serial.println(F("Disabled] "));
    }
}

void SerialPortView::displayWobbulatorFrequencySelectionMenu(const WobbulatorIf *wobbulator, const ViewIf::WobbulatorFrequency frequencyType) const
{
    if (wobbulator != nullptr)
    {
        displayWobbulatorStatus(wobbulator->isEnabled(),
                                wobbulator->isPaused(),
                                wobbulator->getCurrentFrequency(),
                                wobbulator->getStartFrequency(),
                                wobbulator->getEndFrequency());
    }

    Serial.println(F("Frequency menu:"));
    Serial.println(F("Enter frequency in Hz:"));
}

#endif // USE_SERIAL