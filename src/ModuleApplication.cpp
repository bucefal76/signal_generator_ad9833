#include "ModuleApplication.hpp"
#include "Thread.h"

ModuleApplication::ModuleApplication()
{
}

void ModuleApplication::addThread(Thread *pThread)
{
    m_Threads.push_back(pThread);
}

void ModuleApplication::runThreads()
{
    /*
      The Thread library is utilized to simulate time-sharing on a processor,
      similar to what occurs on an operating system. However, this is only an approximation of such behavior,
      as the Thread library does not employ a timer to prompt the task scheduler.
      Instead, it simply keeps track of the number of milliseconds since the last thread activity and executes a thread task when the time comes.
      It's important to note that the loop() function does not control the flow or application logic. All of that occurs within the Thread on Run().
    */

    for (std::vector<Thread *>::iterator it = m_Threads.begin(); it != m_Threads.end(); it++)
    {
        Thread *thread = *it;
        if (nullptr != thread)
        {
            if (thread->shouldRun())
            {
                thread->run();
            }
        }
    }
}