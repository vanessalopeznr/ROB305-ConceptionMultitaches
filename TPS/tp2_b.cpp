//Executer: g++ tp2_b.cpp tp1_a.cpp -o executable.exe

#include <iostream>
#include <string>
#include "time.h"
#include <vector>
#include <cstring>

// double* pCounter ADRESSE
// *pCounter VALEUR

// Struct c'est un classe que tous les variables sont publiques par default
 struct Data {
    volatile unsigned int nLoops;
    double counter;
    pthread_mutex_t mutex;
 };

void incr(unsigned int nLoops, double* pCounter){
    for (int i =0; i < nLoops; i++){
        *pCounter = *pCounter + 1 ;
    }
}

void* call_incr_mut(void* v_data){
    Data* p_data = (Data*) v_data;
    pthread_mutex_lock(&p_data->mutex);
    incr(p_data->nLoops,&p_data->counter); //direccion
    pthread_mutex_unlock(&p_data->mutex);
    return v_data;
}

void* call_incr(void* v_data){
    Data* p_data = (Data*) v_data;
    incr(p_data->nLoops,&p_data->counter);
    return v_data;
}

int main(int argc, char* argv[]){

    // argv es una lista de texto y se debe pasar a int
    unsigned int nLoops = std::stoul(argv[1]);
    std::vector<pthread_t> incrementThread(std::stoul(argv[2]));

    Data data = {nLoops, 0.0 }; pthread_mutex_init(&data.mutex, nullptr);

    timespec time_ts1 = timespec_now();

    for (int i = 0; i < incrementThread.size(); i++){
        if (argc == 4 && std::strcmp(argv[3], "p") == 0 ) {
            std::cout << "Utilisation de Mutex" << std::endl;
            pthread_create(&incrementThread[i], nullptr, call_incr_mut, &data);
        }   
        else {
            std::cout << "Pas d'utilisation de Mutex" << std::endl;
            pthread_create(&incrementThread[i], nullptr, call_incr, &data);
        }
    }

    for (int i=0; i < incrementThread.size(); ++i) pthread_join(incrementThread[i], nullptr);
    pthread_mutex_destroy(&data.mutex);

    timespec time_ts2 = timespec_now();

    double time_ms = timespec_to_ms(time_ts2-time_ts1);
    std::cout << "Time = " << time_ms << std::endl;
    std::cout << "Conteur = " << data.counter << std::endl;

    return 0;
}