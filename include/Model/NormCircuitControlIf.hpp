#ifndef NORMALIZATIONCIRCUITCONTROLIF_HPP
#define NORMALIZATIONCIRCUITCONTROLIF_HPP

#include "ModuleConfig.hpp"

#ifdef USE_NORMALIZATION_CIRCUIT

/*
    Interface to control normalization circuit.
    See /schematics/arduino_uno_application.pdf
*/

class NormCircuitControlIf
{
public:
    /// @brief Method enables an amplification branch in /schematics/arduino_uno_application.pdf
    /// Transistors Q1 and Q5.
    virtual void enableAmplificationBranch() = 0;
    /// @brief Method enables dumping branch in /schematics/arduino_uno_application.pdf
    /// Transistors Q2 and R11.
    virtual void enableDumpingBranch() = 0;
    /// @brief Method disables both branches, no signal at the output.
    virtual void disableBothBranches() = 0;
};

#endif

#endif