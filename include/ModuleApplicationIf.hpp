#ifndef MODULE_APPLICATION_IF_HPP
#define MODULE_APPLICATION_IF_HPP

class Thread;

/*
    Threads created by the user are collected by the application
    object which executes them upon request from main.loop().
*/

class ModuleApplicationIf
{
public:
    /// @brief Add thread to be executer on runThreads call.
    virtual void addThread(Thread *pThread) = 0;
    /// @brief Execute added threads.
    virtual void runThreads() = 0;
};

#endif