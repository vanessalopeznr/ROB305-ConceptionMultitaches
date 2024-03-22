// Executer: g++ tp5.cpp Mutex.cpp PosixThread.cpp CpuLoop.cpp Calibrator.cpp Looper.cpp Timer.cpp time.cpp -o executable.exe

#include <iostream>
#include "Mutex.h"
#include "PosixThread.h"
#include "CpuLoop.h"
#include "Calibrator.h"
#include "Looper.h"
#include "Timer.h"

class CpuLoopThread : public Thread
{
    public:
        CpuLoopThread(Mutex& mutex, CpuLoop& cpuLoop, int policy, int priority);
		~CpuLoopThread();
    
    private:
        CpuLoop cpuLoop;
        Mutex mutex;
        double begin;

    public:

        void run();
    
};

CpuLoopThread::CpuLoopThread(Mutex& mutex, CpuLoop& cpuLoop, int policy, int priority):Thread(), mutex(mutex), cpuLoop(cpuLoop) 
{
    setScheduling(policy, priority);
}
CpuLoopThread::~CpuLoopThread() {}

void CpuLoopThread::run()
{
    
};

int main()
{
    //Turn the code in a single CPU
	cpu_set_t  cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);
	sched_setaffinity(0, sizeof(cpu_set_t), &cpuset);

    int policy = SCHED_RR;
    int priority1 = 5;
    int priority2 = 4;
    int priority3 = 3;

    //Maximun priority for the main thread
    struct sched_param schedParam;
    schedParam.sched_priority = sched_get_priority_max(policy);
    pthread_setschedparam(pthread_self(), policy, &schedParam);
    

    Calibrator calibrator(100.0,10);

    CpuLoop cpuLoopA(calibrator);
    CpuLoop cpuLoopB(calibrator);
    CpuLoop cpuLoopC(calibrator);

    Mutex mutex(false);
    CpuLoopThread ThreadA(mutex, cpuLoopA, policy, priority1);
    CpuLoopThread ThreadB(mutex, cpuLoopB, policy, priority2);
    CpuLoopThread ThreadC(mutex, cpuLoopC, policy, priority3);

    ThreadA.start();
    ThreadB.start();
    ThreadC.start();

    ThreadA.join();
    ThreadB.join();
    ThreadC.join();

    return 0;
}