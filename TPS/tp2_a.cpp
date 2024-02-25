// [Executer] 
// g++ tp2_a.cpp time.cpp -o executable.exe
// ./executable.exe 100000(loop) 5(tasks)

#include <iostream>
#include <string>
#include "time.h"
#include <vector>

// Struct c'est un classe que tous les variables sont publiques par default
 struct Data {
    volatile unsigned long nLoops;
    double counter;
 };

void incr(unsigned int nLoops, double* pCounter){
    for (int i =0; i < nLoops; i++){
        *pCounter = *pCounter + 1 ;
    }
}

void* call_incr(void* v_data){
    Data* p_data = (Data*) v_data;
    incr(p_data->nLoops,&p_data->counter);
    return v_data;
}

int main(int argc, char* argv[]){

    // argv c'est une string et on doit le passer à int ou double
    unsigned long nLoops = std::stoul(argv[1]);
    std::vector<pthread_t> incrementThread(std::stoul(argv[2]));
    
    Data data = {nLoops, 0.0 };

    timespec time_ts1 = timespec_now();

    for (int i = 0; i < incrementThread.size(); i++){
        std::cout << "Tache " << i << std::endl;
        pthread_create(&incrementThread[i], nullptr, call_incr, &data); 
    }

    for (int i=0; i< incrementThread.size(); ++i) pthread_join(incrementThread[i], nullptr);

    timespec time_ts2 = timespec_now();

    double time_ms = timespec_to_ms(time_ts2-time_ts1);
    std::cout << "Time = " << time_ms << std::endl;
    std::cout << "Conteur = " << data.counter << std::endl;

    /*
    //////////////////// REMARQUE ////////////////////

    // incrementThread[nTasks] est un tableau C. Pas autorice en C initial et C++ avec une variable que n'est pas constante
    // Au lieu de cela, on fait un vector avec la taille nTask
    // Initialice le vector: std::vector<pthread_t> incrementThread()
    // nTasks = incrementThread.size()

    // argv es una lista de texto y se debe pasar a int
    unsigned long nLoops = std::stoul(argv[1]);
    unsigned long nTasks = std::stoul(argv[2]);

    Data data = {nLoops, 0.0 };

    timespec time_ts1 = timespec_now();

    pthread_t incrementThread[nTasks];
    for (int i = 0; i < nTasks; i++){
        std::cout << "Tache " << i << std::endl;
        pthread_create(&incrementThread[i], nullptr, call_incr, &data); 
    }

    for (int i=0; i<nTasks; ++i) pthread_join(incrementThread[i], nullptr);

    timespec time_ts2 = timespec_now();


    */

    return 0;
}