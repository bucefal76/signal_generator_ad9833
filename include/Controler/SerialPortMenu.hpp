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
    void displayMainMenu();
    void displayChannel1Menu();
    void displayChannel2Menu();

    static void onRunCallback();

    /// @brief Current state of the menu, a primitive state machine implementation
    enum MenuStateT
    {
        MenuStateStart,
        MenuStateMain,
        MenuStateChannel1Menu,
        MenuStateChannel1EnableDisableMenu,
        MenuStateChannel1SelectSignalTypeMenu,
        MenuStateChannel1SelectFrequencyMenu,
        MenuStateChannel2Menu,
        MenuStateChannel1VobulatorMenu
    };

    MenuStateT m_menuState;

    static SerialPortMenu *m_Instance;
};

#endif