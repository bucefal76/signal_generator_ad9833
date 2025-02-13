#ifndef VOBULATORBYADC_HPP
#define VOBULATORBYADC_HPP

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

    bool state;
};

#endif