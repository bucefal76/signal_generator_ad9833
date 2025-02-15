#ifndef VOBULATOR_HPP
#define VOBULATOR_HPP

#include <Thread.h>

class Vobulator : public Thread
{
public:
    static Vobulator *getInstance();

    Vobulator();

    virtual void enable();
    virtual void disable();

private:
    void update();
    static void onRunCallback();

    static Vobulator *m_Instance;
};

#endif