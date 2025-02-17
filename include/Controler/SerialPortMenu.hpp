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
    virtual void setVobulator(VobulatorIf *vobulator);

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
    /// @brief Helper function to enable the vobulator and disable the generators.
    void enableVobulator();
    /// @brief Helper function to disable the vobulator.
    void disableVobulator();

    void pauseVobulator();
    void resumeVobulator();
    void stepUpVobulator();
    void stepDownVobulator();

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
        MenuStateVobulatorMenu
    };

    MenuStateT m_menuState;
    GeneratorIf::WaveType m_lastSelectedGeneratorChannel1WaveType;
    GeneratorIf::WaveType m_lastSelectedGeneratorChannel2WaveType;
    long m_lastSelectedGeneratorChannel1Frequency;
    long m_lastSelectedGeneratorChannel2Frequency;
    long m_vobulatorStartFrequency;
    long m_vobulatorEndFrequency;
    GeneratorIf *m_generatorChannel1;
    GeneratorIf *m_generatorChannel2;
    ViewIf *m_view;
    VobulatorIf *m_vobulator;

    static SerialPortMenu *m_Instance;
};

#endif

#endif