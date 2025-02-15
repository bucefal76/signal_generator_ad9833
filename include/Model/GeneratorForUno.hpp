#ifndef GENRATORFORUNO_HPP
#define GENRATORFORUNO_HPP

#include "Model/GeneratorIf.hpp"

class AD9833;

class GeneratorForUno : public GeneratorIf
{

public:
    GeneratorForUno(const uint8_t spiCsLine);
    ~GeneratorForUno();
    virtual void setWave(const WaveType type, const uint16_t frequency);
    virtual bool isEnabled() const;
    virtual void disableWave();

private:
    AD9833 *m_AD;
};

#endif