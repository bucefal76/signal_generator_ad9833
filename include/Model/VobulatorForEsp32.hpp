#ifndef VOBULATORFORESP32_HPP
#define VOBULATORFORESP32_HPP

#include "ModuleConfig.hpp"

#ifdef USE_ESP32

#include <Thread.h>
#include "Model/VobulatorIf.hpp"

class GeneratorIf;

#define DAC1_PIN 25
#define DAC2_PIN 26

#define VOBULATOR_NUMBER_OF_STEPS 50

class VobulatorForEsp32 : public Thread, public VobulatorIf
{
public:
    static VobulatorForEsp32 *getInstance();

    VobulatorForEsp32();

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

    virtual void setGenerator(GeneratorIf *generator);

private:
    void update();
    static void onRunCallback();

    GeneratorIf *m_Generator; // Pointer to the generator object
    long m_startFrequency;    // Starting frequency
    long m_endFrequency;      // Ending frequency
    long m_frequencyStep;     // Frequency step
    uint16_t m_currentStep;
    bool m_isPaused;

    static VobulatorForEsp32 *m_Instance;
};

#endif

#endif