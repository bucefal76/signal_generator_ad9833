#ifndef CONTROLLERIF_HPP
#define CONTROLLERIF_HPP

#include "Model/GeneratorIf.hpp"
#include "View/ViewIf.hpp"

/// @brief Interface to define the methods to control the function generators.
/// The interface is used to abstract the implementation of the generator controller from
/// the application, so that the application can use any controller.
class ControllerIf
{
public:
    /// @brief Method to set the generators to control.
    /// @param generatorLine1 Pointer to the first generator to control.
    /// @param generatorLine2 Pointer to the second generator to control.
    virtual void setGeneratorsToControl(GeneratorIf *generatorLine1, GeneratorIf *generatorLine2) = 0;
    /// @brief  Method use to set view do display messages to operator.
    /// @param view Pointer to the view to display messages.
    virtual void setView(ViewIf *view) = 0;
};

#endif