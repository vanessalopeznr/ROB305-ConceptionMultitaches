#ifndef PosixThread_h_INCLUDED
#define PosixThread_h_INCLUDED

#include <pthread.h>

class PosixThread
{
    public:
        using ThreadFunc = void* (*) (void*);

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
        bool setScheduling(int schedPolicy, int priority); // FALTA ??? setScheduling() applique l’ordonnancement et la priorité spécifiée à la tâche (à l’attribut de tâche et à la tâche elle-même si elle est déjà lancée) VERIFICAR
        bool getScheduling(int* p_schedPolicy, int* p_priority);
};

class Thread : public PosixThread
{   
    // Attributs
    public:
        Thread();
        ~Thread();

    //Methods
    public:
        //FALTA
        void start();
        void run();
        void* call_run(void* v_thread);
        void sleep_ms(double delay_ms); //No estoy segura
        double startTime_ms();
        double stopTime_ms();
        double execTime_ms();
};

#endif