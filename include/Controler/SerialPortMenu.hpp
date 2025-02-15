#ifndef SERIALPORTMENU_HPP
#define SERIALPORTMENU_HPP

#ifdef USE_SERIAL

#include <Thread.h>

#include "ControllerIf.hpp"

class SerialPortMenu : public Thread, public ControllerIf
{
public:
    static SerialPortMenu *getInstance();

    SerialPortMenu();

    virtual void enable();
    virtual void disable();

    virtual void setGeneratorsToControl(GeneratorIf *generatorLine1, GeneratorIf *generatorLine2);

private:
    void update();
    void displayMainMenu();
    void displayChannelMenu();
    void displayWaveTypeMenu();
    void displayFrequencyMenu();
    void setGenerator1LineWave(const GeneratorIf::WaveType waveType, const long frequency);
    void setGenerator2LineWave(const GeneratorIf::WaveType waveType, const long frequency);
    void disableGeneratorChannel1();
    void disableGeneratorChannel2();
    void displayChannel1Status();
    void displayChannel2Status();

    static void onRunCallback();

    /// @brief Current state of the menu, a primitive state machine implementation
    enum MenuStateT
    {
        MenuStateStart,
        MenuStateMain,
        MenuStateChannel1Menu,
        MenuStateChannel1SelectWaveTypeMenu,
        MenuStateChannel1SelectFrequencyMenu,
        MenuStateChannel2Menu
    };

    MenuStateT m_menuState;
    GeneratorIf *m_generatorChannel1;
    GeneratorIf *m_generatorChannel2;
    GeneratorIf::WaveType m_lastSelectedGeneratorChannel1WaveType;
    GeneratorIf::WaveType m_lastSelectedGeneratorChannel2WaveType;
    long m_lastSelectedGeneratorChannel1Frequency;
    long m_lastSelectedGeneratorChannel2Frequency;

    static SerialPortMenu *m_Instance;
};

#endif

#endif