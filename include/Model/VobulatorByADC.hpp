#ifndef VOBULATORBYADC_HPP
#define VOBULATORBYADC_HPP

#include "ModuleConfig.hpp"

#ifdef USE_ESP32

#include <Thread.h>

class VobulatorByADC : public Thread
{
public:
    static VobulatorByADC *getInstance();

    VobulatorByADC();

    virtual void enable();
    virtual void disable();

private:
    void update();
    static void onRunCallback();

    static VobulatorByADC *m_Instance;
};

#endif

#endif