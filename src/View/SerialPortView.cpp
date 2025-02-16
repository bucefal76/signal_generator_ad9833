#include "View/SerialPortView.hpp"

#ifdef USE_SERIAL

void SerialPortView::displayMainMenu() const
{
    Serial.println("Main menu:");
    Serial.println("1. Channel 1");
    Serial.println("2. Channel 2");
    Serial.println("3. Vobulator - channel 1");
}

void SerialPortView::displayChannelMenu() const
{
    Serial.println("Channel menu:");
    Serial.println("1. Enable");
    Serial.println("2. Disable");
    Serial.println("3. Select wave type");
    Serial.println("4. Select frequency");
    Serial.println("0. Return to main menu");
}

void SerialPortView::displayWaveTypeMenu() const
{
    Serial.println("Wave type menu:");
    Serial.println("1. Sinusoidal");
    Serial.println("2. Square");
    Serial.println("3. Ramp");
    Serial.println("0. Return to channel menu");
}

void SerialPortView::displayFrequencyMenu() const
{
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
    Serial.println("3. Set start frequency");
    Serial.println("4. Set end frequency");
    Serial.println("0. Return to main menu");
}

#endif // USE_SERIAL