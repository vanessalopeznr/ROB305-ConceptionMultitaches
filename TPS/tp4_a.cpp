// Executer: g++ tp4_a.cpp PosixThread.cpp time.cpp -o executable.exe

#include <iostream>
#include "PosixThread.h"
#include <vector>
#include <cstring>
#include <string>
#include "time.h"

struct Data {
        volatile bool stop;
        volatile int counter;
};

void* incrementer(void* v_data) { //void parce que pthread_create exige une methode void
    Data* p_data = (Data*) v_data;
    while (not p_data->stop) {
        p_data->counter += 1;
        }
    return v_data;
}

 int main(){

    Data data = { false, 0 };
    pthread_t incrementThread;

    PosixThread PosThread(incrementThread);

    // int pthread_create (pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg)
    //pthread_create(&incrementThread, nullptr, incrementer, &data); 
    
    PosThread.start(incrementer,&data);
    for (char cmd = 'r'; cmd != 's'; std::cin >> cmd)
        std::cout << "Type 's' to stop: " << std::flush;
    data.stop = true;

    PosThread.join();
    //pthread_join(incrementThread, nullptr);
    std::cout << "Counter value = " << data.counter << std::endl;
    return 0;
 }
