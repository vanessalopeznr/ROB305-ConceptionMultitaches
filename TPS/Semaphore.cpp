// [TD4-c]

#include "Semaphore.h"
#include "time.h"
#include <pthread.h>

Semaphore::Semaphore(unsigned int initCount, unsigned int maxCount) : counter(initCount), maxCount(maxCount){}

Semaphore::~Semaphore()
{
    std::cout << "The final value of counter was " << counter << "\n";  
}

void Semaphore::give()
{
    Mutex::Lock lock(mutex);
    if (counter < maxCount)
    {
        counter++;
    }
    lock.notifyAll();
}

void Semaphore::take() {
    Mutex::Lock lock(mutex);
    if (counter == 0) {
        lock.wait();
    }
    counter--;
    lock.notify();
}

bool Semaphore::take(double timeout_ms) {
    Mutex::Lock lock(mutex);
    if (counter == 0) {
        if (!lock.wait(timeout_ms)) {
            return false; 
        }
    }
    counter--;
    lock.notify();
    return true;
}
