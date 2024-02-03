#ifndef Mutex_h_INCLUDED
#define Mutex_h_INCLUDED

class Mutex
{
    // Attributs
    public:
        Mutex();
        ~Mutex();

    private:
        pthread_mutex_t posixId;  // Protection multitâches
        pthread_cond_t posixCondId; // Condition

    //Methods
    public:
        // Probablement enlever
        friend void* call_incr_mut();

    private:
        void lock();
        bool lock(double timeout_ms);
        bool trylock();
        void unlock();

};

# endif // Mutex_h
