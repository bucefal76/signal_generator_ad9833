#ifndef GENRATOR_HPP
#define GENRATOR_HPP

class AD9833;

class Generator
{

public:
    Generator();

private:
    AD9833 *m_AD;
};

#endif