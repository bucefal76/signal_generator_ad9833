#ifndef MODULE_APPLICATION_HPP
#define MODULE_APPLICATION_HPP

#include "ModuleApplicationIf.hpp"
#include <vector>

class ModuleApplication : public ModuleApplicationIf
{
public:
    ModuleApplication();
    /// @brief See ModuleApplicationIf::addThread.
    virtual void addThread(Thread *pThread) final;
    /// @brief See ModuleApplicationIf::runThreads.
    virtual void runThreads() final;

private:
    std::vector<Thread *> m_Threads;
};

#endif
