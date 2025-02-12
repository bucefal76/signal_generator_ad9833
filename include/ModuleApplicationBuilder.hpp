#ifndef MODULE_APPLICATION_BUILDER_HPP
#define MODULE_APPLICATION_BUILDER_HPP

/*
    Class wraps application configuration details.
*/

class ModuleApplicationIf;

class ModuleApplicationBuilder
{
public:
    /// @brief Builds the application.
    /// @param rApplication
    void buildApplication(ModuleApplicationIf &rApplication);

protected:
    void setupThreads(ModuleApplicationIf &rApplication);
};

#endif