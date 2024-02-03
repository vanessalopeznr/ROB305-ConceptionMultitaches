// Executer: g++ tp4_b.cpp tp1_a.cpp -o executable.exe

#include <iostream>
#include "Mutex.h"
#include <vector>
#include <cstring>
#include <string>
#include "time.h"

struct Data {
    volatile unsigned int nLoops;
    double counter;
    Mutex mutex;
};

Mutex::Mutex(){
    pthread_mutex_init(&posixId, nullptr);
    pthread_cond_init(&posixCondId, nullptr);
}

Mutex::~Mutex(){
    pthread_mutex_destroy(&posixId);
    pthread_cond_destroy(&posixCondId);
}

//If the mutex is already locked, the calling thread shall block until the mutex becomes available.
void Mutex::lock(){
    pthread_mutex_lock(&posixId);
}

bool Mutex::lock(double timeout_ms){

    return true;
}

//if the mutex is currently locked, the call shall return immediately
bool Mutex::trylock(){
    bool trylock = pthread_mutex_trylock(&posixId);
    return trylock;
}

void Mutex::unlock(){
    pthread_mutex_unlock(&posixId);
}

void incr(unsigned int nLoops, double* pCounter){
    for (int i =0; i < nLoops; i++){
        *pCounter = *pCounter + 1 ;
    }
}

void* call_incr_mut(void* v_data){
    Data* p_data = (Data*) v_data;
    // Je ne sais pas comment utiliser une methode private de la classe Mutex
    p_data->mutex.lock();
    incr(p_data->nLoops,&p_data->counter); //direccion
    pthread_mutex_unlock(&p_data->mutex);
    return v_data;
}

int main(int argc, char* argv[]){

    Mutex myMutex;
    // argv es una lista de texto y se debe pasar a int
    unsigned int nLoops = std::stoul(argv[1]);
    std::vector<pthread_t> incrementThread(std::stoul(argv[2]));

    Data data = {nLoops, 0.0 }; 

    timespec time_ts1 = timespec_now();

    for (int i = 0; i < incrementThread.size(); i++){
        pthread_create(&incrementThread[i], nullptr, call_incr_mut, &data);  
    }

    for (int i=0; i < incrementThread.size(); ++i) pthread_join(incrementThread[i], nullptr);

    timespec time_ts2 = timespec_now();

    double time_ms = timespec_to_ms(time_ts2-time_ts1);
    std::cout << "Time = " << time_ms << std::endl;
    std::cout << "Conteur = " << data.counter << std::endl;

    return 0;
}