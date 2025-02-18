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

    virtual void enable() final;
    virtual void disable() final;

    virtual void setGeneratorsToControl(GeneratorIf *generatorLine1, GeneratorIf *generatorLine2) final;
    virtual void setView(ViewIf *view) final;
    virtual void setWobbulator(WobbulatorIf *wobbulator) final;

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
    /// @brief Helper function to enable the Wobbulator and disable the generators.
    void enableWobbulator();
    /// @brief Helper function to disable the Wobbulator.
    void disableWobbulator();
    /// @brief Helper function to pause Wobbulator auto step.
    void pauseWobbulator();
    /// @brief Helper function to resume Wobbulator auto step.
    void resumeWobbulator();
    /// @brief Helper function to increase Wobbulator step.
    void stepUpWobbulator();
    /// @brief Helper function to decrease Wobbulator step.
    void stepDownWobbulator();
    /// @brief Helper function to set start frequency for Wobbulator sweep.
    void setStartFrequencyForWobbulator(const long frequency);
    /// @brief Helper function to set end frequency for Wobbulator sweep.
    void setEndFrequencyForWobbulator(const long frequency);

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
        MenuStateWobbulatorMenu,
        MenuStateWobbulatorSelectStartFrequencyMenu,
        MenuStateWobbulatorSelectEndFrequencyMenu
    };

    MenuStateT m_menuState;
    GeneratorIf::WaveType m_lastSelectedGeneratorChannel1WaveType;
    GeneratorIf::WaveType m_lastSelectedGeneratorChannel2WaveType;
    long m_lastSelectedGeneratorChannel1Frequency;
    long m_lastSelectedGeneratorChannel2Frequency;
    long m_wobbulatorStartFrequency;
    long m_wobbulatorEndFrequency;
    GeneratorIf *m_generatorChannel1;
    GeneratorIf *m_generatorChannel2;
    ViewIf *m_view;
    WobbulatorIf *m_wobbulator;

    static SerialPortMenu *m_Instance;
};

#endif

#endif