#ifndef CONTROLLERIF_HPP
#define CONTROLLERIF_HPP

#include "Model/GeneratorIf.hpp"

class ControllerIf
{
public:
    virtual void setGeneratorsToControl(GeneratorIf *generatorLine1, GeneratorIf *generatorLine2) = 0;
};

#endif