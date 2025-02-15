#ifndef GENRATORAD9833_HPP
#define GENRATORAD9833_HPP

#include "Model/GeneratorIf.hpp"

class AD9833;

/// @brief Class to generate waves with the AD9833 function generator
/// for the Atmega 328p Arduino Uno and ESP32 Wemos R32 board.
/// This is a common code, it simplifies use of robtillaart/AD9833 library.
/// Lets call this a wrapper class, a convience wrapper class.
class GeneratorAd9833 : public GeneratorIf
{
public:
    GeneratorAd9833();
    virtual ~GeneratorAd9833();
    virtual void generateWave(const WaveType type, const long frequency);
    virtual void disableWave();
    virtual long getFrequency() const;
    virtual WaveType getWaveType() const;
    virtual bool isEnabled() const;

protected:
    /// @brief Pointer to the AD9833 class form the robtillaart/AD9833 library.
    AD9833 *m_AD;
};

#endif