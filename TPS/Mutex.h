#ifndef Mutex_h_INCLUDED
#define Mutex_h_INCLUDED

class Mutex
{
    // Attributs
    public:
        Mutex();
        ~Mutex();

    private:
        pthread_mutex_t posixId;
        pthread_cond_t posixCondId;

    //Methods
    private:
        void lock();
        bool lock(double timeout_ms);
        bool trylock();
        void unlock();

};

# endif // Mutex_h
