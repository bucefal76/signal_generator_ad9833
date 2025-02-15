#ifndef GENRATORFORUNO_HPP
#define GENRATORFORUNO_HPP

#include "Model/GeneratorIf.hpp"

class AD9833;

/// @brief Class to generate waves with the AD9833 function generator
class GeneratorForUno : public GeneratorIf
{

public:
    GeneratorForUno(const uint8_t spiCsLine);
    ~GeneratorForUno();
    virtual void generateWave(const WaveType type, const long frequency);
    virtual void disableWave();
    virtual long getFrequency() const;
    virtual WaveType getWaveType() const;
    virtual bool isEnabled() const;

private:
    AD9833 *m_AD;
};

#endif