#ifndef VOBULATORBASE_HPP
#define VOBULATORBASE_HPP

#include "ModuleConfig.hpp"

#include "Model/WobbulatorIf.hpp"
#include <Thread.h>

class GeneratorIf;

#define DAC1_PIN 25
#define DAC2_PIN 26

#define VOBULATOR_NUMBER_OF_STEPS 50

class WobbulatorBase : public Thread, public WobbulatorIf
{
public:
    static WobbulatorBase *getInstance();

    WobbulatorBase();

    virtual void enable() final;
    virtual void disable() final;
    virtual void pause() final;
    virtual void resume() final;
    virtual void stepUp() final;
    virtual void stepDown();
    virtual long getCurrentFrequency() const final;
    virtual bool isEnabled() const final;
    virtual bool isPaused() const final;
    virtual long getStartFrequency() const final;
    virtual long getEndFrequency() const final;
    virtual void setStartFrequency(const long startFrequency) final;
    virtual void setEndFrequency(const long endFrequency) final;
    virtual void setGenerator(GeneratorIf *generator) final;
    virtual void setsSettingsStorage(SettingsIf *settingsStorage) final;

    // virtual void setRampSignalValue(const uint16_t )

private:
    void update();
    static void onRunCallback();

    GeneratorIf *m_Generator;
    SettingsIf *m_Settings;
    long m_FrequencyStep;
    uint16_t m_CurrentStepNo;
    bool m_IsPaused;

    static WobbulatorBase *m_Instance;
};

#endif