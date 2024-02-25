// [TD4-b] 

// Executer: g++ tp4_b.cpp tp1_a.cpp -o executable.exe

#include "Mutex.h"
#include "time.h"

// --------------------------------- MUTEX ---------------------------------

Mutex::Mutex()
{
    pthread_mutex_init(&posixId, nullptr);
    pthread_cond_init(&posixCondId, nullptr);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&posixId);
    pthread_cond_destroy(&posixCondId);
}

//If the mutex is already locked, the calling thread shall block until the mutex becomes available.
void Mutex::lock()
{
    pthread_mutex_lock(&posixId);
}

bool Mutex::lock(double timeout_ms)
{
    timespec delay_time = timespec_from_ms(timeout_ms);
    timespec actual_time = timespec_now();
    timespec abs_time = actual_time + delay_time;
    return 0 == pthread_mutex_timedlock(&posixId, &abs_time); // 0 if success
}

//if the mutex is currently locked, the call shall return immediately
bool Mutex::trylock()
{
    return pthread_mutex_trylock(&posixId);
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&posixId);
}


// --------------------------------- MONITOR ---------------------------------

Mutex::Monitor::Monitor(Mutex& mtx) : mutex(mtx) // You must immediately say which mutex you are referring to, you initialize it by saying that the mutex is the mutex passed in the attributes
{
    // For constants and references, the only way to initialize them is at the beginning when the class is created. Ej. const int x; i have to initialize as mutex(mtx) i.e. x(0)
}

void Mutex::Monitor::wait()
{
    pthread_cond_wait(&mutex.posixCondId, &mutex.posixId);
}

bool Mutex::Monitor::wait(double timeout_ms)
{
    timespec delay_time = timespec_from_ms(timeout_ms);
    timespec actual_time = timespec_now();
    timespec abs_time = actual_time + delay_time;
    return 0 == pthread_cond_timedwait(&mutex.posixCondId, &mutex.posixId, &abs_time); // 0 if success
}

void Mutex::Monitor::notify()
{
    pthread_cond_signal(&mutex.posixCondId);
}

void Mutex::Monitor::notifyAll()
{
     pthread_cond_broadcast(&mutex.posixCondId);
}


// --------------------------------- LOCK ---------------------------------

Mutex::Lock::Lock(Mutex& mtx) : Monitor(mtx) // Everything that is inherited must be initialized by the constructor of the parent class.
{
    mutex.lock();
}

Mutex::Lock::Lock(Mutex& mutex, double timeout_ms) : Monitor(mutex)
{
    if (mutex.lock(timeout_ms)) // if mutex.lock(timeout_ms) == True:
    {
        throw TimeoutException();
    }
}

Mutex::Lock::~Lock()
{
    mutex.unlock();
}

