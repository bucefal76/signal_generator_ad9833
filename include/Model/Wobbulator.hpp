#ifndef VOBULATORBASE_HPP
#define VOBULATORBASE_HPP

#include "ModuleConfig.hpp"

#include "Model/WobbulatorIf.hpp"
#include <Thread.h>

class GeneratorIf;

class Wobbulator : public Thread, public WobbulatorIf
{
public:
    static Wobbulator *getInstance();

    Wobbulator();

    virtual void enable() final;
    virtual void disable() final;
    virtual void pause() final;
    virtual void resume() final;
    virtual void stepUp() final;
    virtual void stepDown();
    virtual unsigned long getCurrentFrequency() const final;
    virtual bool isEnabled() const final;
    virtual bool isPaused() const final;
    virtual unsigned long getStartFrequency() const final;
    virtual unsigned long getEndFrequency() const final;
    virtual void setStartFrequency(const unsigned long startFrequency) final;
    virtual void setEndFrequency(const unsigned long endFrequency) final;
    virtual void setGenerator(GeneratorIf *generator) final;
    virtual void setSettingsStorage(SettingsIf *settingsStorage) final;
    virtual void setRampSignal(RampSignalIf *rampSignalSource) final;

private:
    void update();
    static void onRunCallback();

    GeneratorIf *m_Generator;
    SettingsIf *m_Settings;
    RampSignalIf *m_RampSignalSource;
    unsigned long m_FrequencyStep;
    uint16_t m_CurrentStepNo;
    bool m_IsPaused;

    static Wobbulator *m_Instance;
};

#endif