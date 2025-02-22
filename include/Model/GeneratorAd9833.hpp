#ifndef GENRATORAD9833_HPP
#define GENRATORAD9833_HPP

#include "Model/GeneratorIf.hpp"

class AD9833;

#define TEST_VALUE 0x55AA

/// @brief Class to generate waves with the AD9833 function generator
/// for the Atmega 328p Arduino Uno and ESP32 Wemos R32 board.
/// This is a common code, it simplifies use of robtillaart/AD9833 library.
/// Lets call this a wrapper class, a convience wrapper class.
class GeneratorAd9833 : public GeneratorIf
{
public:
    GeneratorAd9833(const uint8_t channelId);
    virtual ~GeneratorAd9833();

    virtual uint8_t getChannelId() const override;
    virtual void generateWave(const WaveType type, const long frequency) override;
    virtual void disableWave() override;
    virtual long getFrequency() const override;
    virtual WaveType getWaveType() const override;
    virtual bool isEnabled() const override;

protected:
    /// @brief This is a blocking method to test if we can connect with the AD9833.
    void connectivityTest();

    /// @brief Pointer to the AD9833 class form the robtillaart/AD9833 library.
    AD9833 *m_AD;
    /// @brief The channel id of the generator.
    uint8_t m_ChannelId;
};

#endif