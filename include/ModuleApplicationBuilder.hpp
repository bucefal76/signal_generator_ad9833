#ifndef MODULE_APPLICATION_BUILDER_HPP
#define MODULE_APPLICATION_BUILDER_HPP

/*
    Class wraps application configuration details.
    This is a "dirtY" code as it is named in the book.
    I'm referring Clean Code by Robert C. Martin.
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