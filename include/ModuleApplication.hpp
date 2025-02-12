#ifndef MODULE_APPLICATION_HPP
#define MODULE_APPLICATION_HPP

#include "ModuleApplicationIf.hpp"
#include <vector>

class ModuleApplication : public ModuleApplicationIf
{
public:
    ModuleApplication();
    /// @brief See ModuleApplicationIf::addThread.
    virtual void addThread(Thread *pThread);
    /// @brief See ModuleApplicationIf::runThreads.
    virtual void runThreads();

private:
    std::vector<Thread *> m_Threads;
};

#endif
