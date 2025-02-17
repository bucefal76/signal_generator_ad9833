#include "View/SerialPortView.hpp"

#ifdef USE_SERIAL

void SerialPortView::displayMainMenu(const GeneratorIf *generator1, const GeneratorIf *generator2) const
{
    if (generator1 != nullptr)
    {
        displayChannelStatus(generator1->getChannelId(), generator1->isEnabled(), generator1->getWaveType(), generator1->getFrequency());
    } 
    if (generator2 != nullptr)
    {
        displayChannelStatus(generator1->getChannelId(), generator2->isEnabled(), generator2->getWaveType(), generator2->getFrequency());
    }
    Serial.println("Main menu:");
    Serial.println("1. Channel 1");
    Serial.println("2. Channel 2");
    Serial.println("3. Vobulator - channel 1");
}

void SerialPortView::displayChannelMenu(const GeneratorIf *generator) const
{
    if (generator != nullptr)
    {
        displayChannelStatus(generator->getChannelId(), generator->isEnabled(), generator->getWaveType(), generator->getFrequency());
    }
    Serial.println("Channel menu:");
    Serial.println("1. Enable");
    Serial.println("2. Disable");
    Serial.println("3. Select wave type");
    Serial.println("4. Select frequency");
    Serial.println("0. Return to main menu");
}

void SerialPortView::displayWaveTypeMenu(const GeneratorIf *generator) const
{
    if (generator != nullptr)
    {
        displayChannelStatus(generator->getChannelId(), generator->isEnabled(), generator->getWaveType(), generator->getFrequency());
    }
    Serial.println("Wave type menu:");
    Serial.println("1. Sinusoidal");
    Serial.println("2. Square");
    Serial.println("3. Ramp");
    Serial.println("0. Return to channel menu");
}

void SerialPortView::displayFrequencyMenu(const GeneratorIf *generator) const
{
    if (generator != nullptr)
    {
        displayChannelStatus(generator->getChannelId(), generator->isEnabled(), generator->getWaveType(), generator->getFrequency());
    }
    Serial.println("Frequency menu:");
    Serial.println("Enter frequency in Hz:");
}

void SerialPortView::displayChannelStatus(const uint8_t channelId, const bool channelEnabled, const GeneratorIf::WaveType waveType, const long frequency) const
{
    Serial.print("Channel ");
    Serial.print(channelId);
    Serial.print(": [State: ");
    if (channelEnabled)
    {
        Serial.print("Enabled, ");
    }
    else
    {
        Serial.print("Disabled, ");
    }
    Serial.print("Wave type: ");
    switch (waveType)
    {
    case GeneratorIf::TypeSinusoidal:
        Serial.print("Sinusoidal");
        break;
    case GeneratorIf::TypeSquare:
        Serial.print("Square");
        break;
    case GeneratorIf::TypeRamp:
        Serial.print("Ramp");
        break;
    default:
        Serial.print("None");
        break;
    }
    Serial.print(", Frequency: ");
    Serial.print(frequency);
    Serial.println(" Hz]");
}

void SerialPortView::displayVobulatorMenu() const
{
    Serial.println("Vobulator menu:");
    Serial.println("1. Enable");
    Serial.println("2. Disable");
    Serial.println("3. Pause");
    Serial.println("4. Resume");
    Serial.println("5. Step up");
    Serial.println("6. Step down");
    Serial.println("7. Set start frequency");
    Serial.println("8. Set end frequency");
    Serial.println("0. Return to main menu");
}

#endif // USE_SERIAL