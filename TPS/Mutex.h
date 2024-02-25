#ifndef Mutex_h_INCLUDED
#define Mutex_h_INCLUDED

    #include <pthread.h>

class Mutex
{
    //Class
    public:
        class Monitor;
        class Lock;

    // Attributs
    public:
        Mutex();
        ~Mutex(); //No necesidad de declarar destructor mutex virutal porque no vamos a hacer polimorfismo (no hay clase que deriva de otra)

    private:
        pthread_mutex_t posixId;  // Protection multitâches
        pthread_cond_t posixCondId; // Condition

    // Methods
    private:
        void lock();
        bool lock(double timeout_ms);
        bool trylock();
        void unlock();

};

// When I declare a class in a file of another class, the other class plays the role of main space
// In the diagram, the monitor class is given mutex as attribute
class Mutex::Monitor{

    //Classes
    public:
        class TimeoutException{};

    //Attributs
    public:
        Monitor(Mutex& mtx);
    
    protected:
        Mutex& mutex;

    //Methods
    public:
        void wait();
        bool wait(double timeout_ms);
        void notify();
        void notifyAll();

};

class Mutex::Lock : public Monitor //Class mutex derived the Monitor
{
    public:
        Lock(Mutex& mutex);
        Lock(Mutex& mutex, double timeout_ms);
        ~Lock();

};

# endif // Mutex_h
