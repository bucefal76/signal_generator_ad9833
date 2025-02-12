#ifndef SERIALPORTMENU_HPP
#define SERIALPORTMENU_HPP

#include <Thread.h>

class SerialPortMenu : public Thread
{
public:
    static SerialPortMenu *getInstance();

    SerialPortMenu();

    virtual void enable();
    virtual void disable();

private:
    void update();
    static void onRunCallback();

    static SerialPortMenu *m_Instance;
};

#endif