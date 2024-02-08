#ifndef PosixThread_h_INCLUDED
#define PosixThread_h_INCLUDED

class PosixThread
{
    public:
        using ThreadFunc = void* (*) (void*)

    private:
        pthread_t posixId;
        pthread_attr_t posixAttr;
        bool isActive;

    public:
        PosixThread();
        PosixThread(pthread_t posixId);
        ~PosixThread();
        //void start(void* (*threadFunc) (void*)); //Puntero de funcion [*threadFunc]= Gauche: type (return); Droit: parametre
        void start(ThreadFunc threadFunc, void* threadArg);
        void join();
        bool join(double timeout_ms);
        bool setScheduling(int schedPolicy, int priority);
        bool getScheduling(int* p_schedPolicy, int* p_priority);
}   

#endif