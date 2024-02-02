#include <iostream>
#include <pthread.h>

//Creation d'une tache

void* incrementer(void* v_stop) {
    
    volatile bool* p_stop = (volatile bool*) v_stop;
    double counter = 0.0;
    while (not *p_stop) {
    counter += 1.0;
    }
    std::cout << "Counter value = " << counter << std::endl;
    return v_stop;
}

int main(){

    volatile bool stop = false;
    pthread_t incrementThread; 

    // int pthread_create (pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg)
    pthread_create(&incrementThread, nullptr, incrementer, (void*) &stop); 
    for (char cmd = 'r'; cmd != 's'; std::cin >> cmd)
        std::cout << "Type 's' to stop: " << std::flush;
    stop = true;
    
    // pthread_join espera que todos los procesos se terminen antes de tumbar el main (cierra todos los procesos)
    pthread_join(incrementThread, nullptr);

    return 0;
}
