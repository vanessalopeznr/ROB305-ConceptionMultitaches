// [Executer] 
// g++ tp1_c.cpp time.cpp -o executable.exe
// ./executable 100(MaxCounter)

#include <iostream>
#include <string>
#include "time.h"

// double* pCounter ADRESSE
// *pCounter VALEUR

void incr(unsigned int nLoops, double* pCounter){
    for (int i =0; i < nLoops; i++){
        *pCounter = *pCounter + 1 ;
        std::cout << *pCounter << std::endl;
    }
}

int main(int argc, char* argv[]){

    // argv es una lista de texto y se debe pasar a int
    unsigned int nLoops = std::stoul(argv[1]);

    double Counter; //Crear variable
    double* pCount = &Counter; //Crear puntero a la posicion de memoria de la variable
    *pCount = 0; //Asignar valor a esa posicion de memoria

    timespec time_ts1 = timespec_now();
    
    incr(nLoops,pCount);

    timespec time_ts2 = timespec_now();

    double time_ms = timespec_to_ms(time_ts2-time_ts1);
    std::cout << "Time" << time_ms << std::endl;

    return 0;
}