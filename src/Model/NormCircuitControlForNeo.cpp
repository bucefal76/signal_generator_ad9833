#include "Model/NormCircuitControlForNeo.hpp"
#include <Arduino.h>

#ifdef USE_NORMALIZATION_CIRCUIT

#define CHANNEL1_OUTPUT_SWITCH 9
#define CHANNEL2_OUTPUT_SWITCH 8
#define CHANNEL1_SHORT_SWITCH 7
#define CHANNEL2_SHORT_SWITCH 6

NormCircuitControlForNeo::NormCircuitControlForNeo()
{
    pinMode(CHANNEL1_OUTPUT_SWITCH, OUTPUT);
    pinMode(CHANNEL2_OUTPUT_SWITCH, OUTPUT);
    pinMode(CHANNEL1_SHORT_SWITCH, OUTPUT);
    pinMode(CHANNEL2_SHORT_SWITCH, OUTPUT);

    digitalWrite(CHANNEL2_OUTPUT_SWITCH, LOW);
    digitalWrite(CHANNEL1_OUTPUT_SWITCH, LOW);
    digitalWrite(CHANNEL1_SHORT_SWITCH, HIGH);
    digitalWrite(CHANNEL2_SHORT_SWITCH, HIGH);
}

void NormCircuitControlForNeo::enableAmplificationBranch()
{
    // Block channel 2
    digitalWrite(CHANNEL2_OUTPUT_SWITCH, LOW);
    digitalWrite(CHANNEL2_SHORT_SWITCH, HIGH);
    // Enable channel 1
    digitalWrite(CHANNEL1_SHORT_SWITCH, LOW);
    digitalWrite(CHANNEL1_OUTPUT_SWITCH, HIGH);
}

void NormCircuitControlForNeo::enableDumpingBranch()
{
    // Block channel 1
    digitalWrite(CHANNEL1_OUTPUT_SWITCH, LOW);
    digitalWrite(CHANNEL1_SHORT_SWITCH, HIGH);
    // Enable channel 2
    digitalWrite(CHANNEL2_SHORT_SWITCH, LOW);
    digitalWrite(CHANNEL2_OUTPUT_SWITCH, HIGH);
}

void NormCircuitControlForNeo::disableBothBranches()
{
    digitalWrite(CHANNEL1_OUTPUT_SWITCH, LOW);
    digitalWrite(CHANNEL2_OUTPUT_SWITCH, LOW);
    digitalWrite(CHANNEL1_SHORT_SWITCH, HIGH);
    digitalWrite(CHANNEL2_SHORT_SWITCH, HIGH);
}

#endif