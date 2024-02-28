// [TD4-a]

#include "PosixThread.h"
#include "time.h"
#include <iostream>


// --------------------------------- POSIXTHREAD ---------------------------------


// Pas inicialise dans les blocks
PosixThread::PosixThread(): posixId(0), isActive(false)
{
    std::cout << "Inicialice posixId en 0" << std::endl;
    pthread_attr_init(&posixAttr);
}

PosixThread::PosixThread(pthread_t posixId): posixId(posixId), isActive(false)
{
    pthread_attr_init(&posixAttr);
    int schedPolicy;
    sched_param schedp;
    std::cout << "Inicialice posixId en pthread" << std::endl;
    //Test the validity of a thread identifier.
    if (pthread_getschedparam(posixId, &schedPolicy, &schedp)<0)
    {
        isActive = false;
        posixId = 0;
    }
    pthread_attr_setschedpolicy(&posixAttr, schedPolicy);
    pthread_attr_setschedparam(&posixAttr, &schedp);
}

PosixThread::~PosixThread()
{
    pthread_attr_destroy(&posixAttr);
}

void PosixThread::start(ThreadFunc threadFunc, void* threadArg)
{
    isActive=true;
    pthread_create(&posixId, nullptr, threadFunc, threadArg); 
}

void PosixThread::join()
{
    // waits the thread posixId to terminate
    pthread_join(posixId, nullptr);
}

bool PosixThread::join(double timeout_ms)
{
    timespec delay_time = timespec_from_ms(timeout_ms);
    timespec actual_time = timespec_now();
    timespec abs_time = actual_time + delay_time;
    return 0 == pthread_timedjoin_np(posixId,nullptr,&abs_time); //0 if success
}

bool PosixThread::setScheduling(int schedPolicy, int priority)
{
    sched_param schedp;
    schedp.sched_priority = priority;
    // À partir de pthread_setschedparam, toute nouvelle tâche hérite de la politique de main
    return 0 == pthread_setschedparam(posixId, schedPolicy, &schedp); //0 if success
}

bool PosixThread::getScheduling(int* p_schedPolicy, int* p_priority)
{
    sched_param schedp;
    schedp.sched_priority = *p_priority;
    //Test the validity of a thread identifier.
    return 0 == pthread_getschedparam(posixId, p_schedPolicy, &schedp);
}

// --------------------------------- THREAD ---------------------------------

Thread::Thread() : PosixThread()
{

}

Thread::~Thread()
{
    
}

void Thread::start()
{
    StartTime = startTime_ms();
    PosixThread::start(&Thread::call_run,this);
}
void* Thread::call_run(void* v_thread)
{
    // Another instance of Thread is created because in a static class you don't have access to non-static member
    Thread* new_Thread = (Thread*)v_thread;
    new_Thread->run();
    new_Thread-> StopTime = new_Thread->stopTime_ms();
    return new_Thread;
}
//void* Thread::call_run(void* v_thread){}
void Thread::sleep_ms(double delay_ms)
{
    timespec delay_ts = timespec_from_ms(delay_ms);
    timespec_wait(delay_ts);

}
double Thread::startTime_ms()
{
    timespec actual_time = timespec_now();
    return timespec_to_ms(actual_time);
}
double Thread::stopTime_ms()
{
    timespec actual_time = timespec_now();
    return timespec_to_ms(actual_time);
}
double Thread::execTime_ms()
{
    return StopTime - StartTime;
}