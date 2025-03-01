#ifndef NORMALIZATIONCIRCUITCONTROLFORNEO_HPP
#define NORMALIZATIONCIRCUITCONTROLFORNEO_HPP

#include "Model/NormCircuitControlIf.hpp"

#ifdef USE_NORMALIZATION_CIRCUIT

/// @brief This is NormCircuitControlIf implementation
/// for the Arduino UNO or NANO.
class NormCircuitControlForNeo : public NormCircuitControlIf
{
public:
    NormCircuitControlForNeo();

    virtual void enableAmplificationBranch() final;
    virtual void enableDumpingBranch() final;
    virtual void disableBothBranches() final;
};

#endif

#endif