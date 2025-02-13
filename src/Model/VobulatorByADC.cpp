#include "Model/VobulatorByADC.hpp"

#ifdef USE_ESP32

#include <math.h>
#include <stdint.h>

#include <esp_task_wdt.h>

#define DAC1_PIN 25
#define DAC2_PIN 26

#define SINE_TABLE_SIZE 256
#define RAMP_TABLE_SIZE 25

uint8_t sineTable[SINE_TABLE_SIZE];

uint8_t rampTable[RAMP_TABLE_SIZE];

void generateSineTable()
{
    for (int i = 0; i < SINE_TABLE_SIZE; i++)
    {
        float angle = (2.0f * M_PI * i) / SINE_TABLE_SIZE;     // Calculate the angle in radians
        float sineValue = sin(angle);                          // Get the sine value
        sineTable[i] = (uint8_t)((sineValue + 1.0f) * 127.5f); // Scale to 0-255 range
    }
}

void generateRampTable()
{
    for (int i = 0; i < RAMP_TABLE_SIZE; i++)
    {
        rampTable[i] = i; // Calculate the ramp value
    }
}

void generateRampTable(int num_samples)
{
    for (int i = 0; i < num_samples; i++)
    {
        rampTable[i] = 0xFF - (i * 0xFF / (num_samples - 1)); // Calculate the ramp value
    }
}

bool S = true;

VobulatorByADC *VobulatorByADC::m_Instance = nullptr;

VobulatorByADC *VobulatorByADC::getInstance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new VobulatorByADC();
    }

    return m_Instance;
}

VobulatorByADC::VobulatorByADC()
{
    setInterval(VOBULATOR_BY_DC_THREAD_TIME_INTERVAL_MS);
    onRun(onRunCallback);
    enabled = false;

    generateSineTable();
    generateRampTable(RAMP_TABLE_SIZE);
}

void VobulatorByADC::enable()
{
    enabled = true;
}

void VobulatorByADC::disable()
{
    enabled = false;
}

void VobulatorByADC::update()
{
    for (uint16_t j = 0; j < RAMP_TABLE_SIZE; j++)
    {
        dacWrite(DAC2_PIN, rampTable[j]);

        for (uint8_t cycles = 0; cycles < 5; cycles++)
        {
            for (uint16_t i = 0; i < SINE_TABLE_SIZE; i++)
            {
                dacWrite(DAC1_PIN, sineTable[i]);
            }
        }
    }

    // esp_task_wdt_reset();
}

void VobulatorByADC::onRunCallback()
{
    m_Instance->update();
}

#endif