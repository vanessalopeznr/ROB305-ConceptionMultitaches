#ifndef CpuLoopThread_h_INCLUDED
#define CpuLoopThread_h_INCLUDED

#include "CpuLoop.h"
#include "PosixThread.h"
#include "Mutex.h"
#include "Calibrator.h"
#include <signal.h>

class CpuLoopThread : public Thread
{
    public:
        CpuLoopThread(Mutex& mutex, CpuLoop& cpuLoop);
		~CpuLoopThread();
        CpuLoop cpuLoop;
        Mutex mutex;
        double begin;

    public:

        void run();
    
};

# endif // Mutex_h