// Executer: g++ tp5.cpp Mutex.cpp PosixThread.cpp CpuLoop.cpp Calibrator.cpp Looper.cpp Timer.cpp time.cpp -o executable.exe

#include <iostream>
#include "Mutex.h"
#include "PosixThread.h"
#include "CpuLoop.h"
#include "Calibrator.h"
#include "Looper.h"
#include "Timer.h"
#include "time.h"


class CpuLoopThread : public Thread
{
    public:
        CpuLoopThread(Mutex* mtx, Calibrator* calibrator,  double duration, bool needsMutex, double timeStartLock = 0, double timeDurationLock = 0);
        ~CpuLoopThread();

    private:
        Mutex* mutex;
        CpuLoop* looper;

        double timeDuration_ms;
        double timeStartLock_ms;
        double timeDurationLock_ms;

        bool needsMutex_bool;

        double timeBegin_ms;
        double timeEnd_ms;
    
    public:
        void run(void) override;
        double getTimeBegin_ms() const { return timeBegin_ms; }
        double getTimeEnd_ms() const { return timeEnd_ms; }

};

CpuLoopThread::CpuLoopThread(Mutex* mtx, Calibrator* calibrator, double duration, bool needsMutex, double timeStartLock, double timeDurationLock)
    : mutex(mtx),
      timeDuration_ms(duration),
      needsMutex_bool(needsMutex),
      timeStartLock_ms(timeStartLock),
      timeDurationLock_ms(timeDurationLock),
      looper(new CpuLoop(*calibrator)) {
}


CpuLoopThread::~CpuLoopThread(){}


void CpuLoopThread::run()
{
    timeBegin_ms = timespec_to_ms(timespec_now());
    if (!needsMutex_bool)
    {
        looper->runTime(timeDuration_ms);
    }

    else
    {
        looper->runTime(timeStartLock_ms);
        
        Mutex::Lock lock(*mutex);
        looper->runTime(timeDurationLock_ms);
        lock.~Lock();
    
        looper->runTime(timeDuration_ms - timeStartLock_ms - timeDurationLock_ms);
    }
    timeEnd_ms = timespec_to_ms(timespec_now());
}



int main(int argc, char* argv[])
{   
    std::cout << "Début du programme..." << std::endl;
    // On va utiliser qu'un seul CPU pour la suite
    cpu_set_t mask;

    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    std::cout << "CPU configuré." << std::endl;


    // Definir la priorité
    PosixThread main(pthread_self());
    main.setScheduling(SCHED_FIFO, sched_get_priority_max(SCHED_FIFO));
    std::cout << "Priorité du thread principal définie." << std::endl;

    // Iniitaliser le mutex
    bool isInversionSafe = true;
    Mutex mutex(isInversionSafe);

    // Calibrer le temps par tick
    double samplingPeriod_ms = 5;
    unsigned int nSamples = 500;
    Calibrator calibrator(samplingPeriod_ms, nSamples);
    std::cout << "Calibrateur initialisé." << std::endl;
    

    // Paramètres de chaque tâche
    double timeDurationA_ms = 400;
    double timeDurationB_ms = 100;
    double timeDurationC_ms = 500;

    double timeStartLockA_ms = 100;
    double timeStartLockC_ms = 200;

    double timeDurationLockA_ms = 100;
    double timeDurationLockC_ms = 200;

    
    CpuLoopThread A(&mutex, &calibrator, timeDurationA_ms, true, timeStartLockA_ms, timeDurationLockA_ms);
    CpuLoopThread B(&mutex, &calibrator, timeDurationB_ms, false);
    CpuLoopThread C(&mutex, &calibrator, timeDurationC_ms, true, timeDurationLockA_ms, timeDurationLockC_ms);
    A.setScheduling(SCHED_FIFO, 99);
    B.setScheduling(SCHED_FIFO, 50);
    C.setScheduling(SCHED_FIFO, 10);
    std::cout << "Tâches A, B, et C initialisés." << std::endl;

    double timeStart_ms = timespec_to_ms(timespec_now());

    C.start();
    timespec_wait(timespec_from_ms(300));
    B.start();
    A.start();

    C.join();
    B.join();
    A.join();

    std::cout << "Tâche A commencée à " << A.getTimeBegin_ms() - timeStart_ms << " et terminée à " << A.getTimeEnd_ms() - timeStart_ms << "ms." << std::endl;

    std::cout << "Tâche B commencée à " << B.getTimeBegin_ms()  - timeStart_ms << " et terminée à " << B.getTimeEnd_ms() - timeStart_ms << "ms." << std::endl;

    std::cout << "Tâche C commencée à " << C.getTimeBegin_ms() - timeStart_ms << " et terminée à " << C.getTimeEnd_ms() - timeStart_ms << "ms." << std::endl;

    std::cout << "Programme terminé." << std::endl;
    
    return 0;
}