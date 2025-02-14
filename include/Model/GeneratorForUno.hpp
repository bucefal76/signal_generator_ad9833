#ifndef GENRATORFORUNO_HPP
#define GENRATORFORUNO_HPP

#include "Model/GeneratorIf.hpp"

class AD9833;

class GeneratorForUno : public GeneratorIf
{

public:
    GeneratorForUno(const uint8_t spiCsLine);
    virtual void enableGenerator(const GetTypes type, const uint16_t frequency);
    virtual void disableGenerator();

private:
    AD9833 *m_AD;
};

#endif