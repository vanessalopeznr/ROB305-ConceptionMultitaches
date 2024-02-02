#include <iostream>

//Partage de donnees entre taches

struct Data {
        volatile bool stop;
        volatile double counter;
};

void* incrementer(void* v_data) { //void
    Data* p_data = (Data*) v_data;
    while (not p_data->stop) {
        p_data->counter += 1.0;
        }
    return v_data;
}

 int main(){

    Data data = { false, 0.0 };
    pthread_t incrementThread;

    // int pthread_create (pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg)
    pthread_create(&incrementThread, nullptr, incrementer, &data); 
    for (char cmd = 'r'; cmd != 's'; std::cin >> cmd)
        std::cout << "Type 's' to stop: " << std::flush;
    data.stop = true;

    pthread_join(incrementThread, nullptr);
    std::cout << "Counter value = " << data.counter << std::endl;
    return 0;
 }