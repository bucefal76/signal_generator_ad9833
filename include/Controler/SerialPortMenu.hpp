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
    virtual void setView(ViewIf *view);

private:
    /// @brief Main function of the thread
    void update();
    /// @brief  Set the wave type and frequency of the generator (first one).
    /// @param waveType Type of the wave.
    /// @param frequency The frequency of the wave.
    void setGeneratorChannel1Wave(const GeneratorIf::WaveType waveType, const long frequency);
    /// @brief  Set the wave type and frequency of the generator (second one).
    /// @param waveType Type of the wave.
    /// @param frequency The frequency of the wave.
    void setGeneratorChannel2Wave(const GeneratorIf::WaveType waveType, const long frequency);
    /// @brief Helper function to disable the first generator.
    void disableGeneratorChannel1();
    /// @brief Helper function to disable the second generator.
    void disableGeneratorChannel2();
    /// @brief Helper function to display the status of the first channel
    void displayChannel1Status();
    // @brief Helper function to display the status of the second channel
    void displayChannel2Status();
    /// @brief Callback function to run the thread.
    static void onRunCallback();

    /// @brief Current state of the menu, a primitive state machine implementation
    enum MenuStateT
    {
        MenuStateStart,
        MenuStateMain,
        MenuStateChannel1Menu,
        MenuStateChannel1SelectWaveTypeMenu,
        MenuStateChannel1SelectFrequencyMenu,
        MenuStateChannel2Menu,
        MenuStateChannel2SelectWaveTypeMenu,
        MenuStateChannel2SelectFrequencyMenu,
    };

    MenuStateT m_menuState;
    GeneratorIf *m_generatorChannel1;
    GeneratorIf *m_generatorChannel2;
    ViewIf *m_view;
    GeneratorIf::WaveType m_lastSelectedGeneratorChannel1WaveType;
    GeneratorIf::WaveType m_lastSelectedGeneratorChannel2WaveType;
    long m_lastSelectedGeneratorChannel1Frequency;
    long m_lastSelectedGeneratorChannel2Frequency;

    static SerialPortMenu *m_Instance;
};

#endif

#endif