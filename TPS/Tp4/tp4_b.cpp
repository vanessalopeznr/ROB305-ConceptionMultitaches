// Executer: g++ tp4_b.cpp Mutex.cpp time.cpp -o executable.exe

#include <iostream>
#include "Mutex.h"
#include <vector>
#include <cstring>
#include <string>
#include "time.h"

int main(){

    Mutex mtx;

    Mutex::Monitor monit(mtx);
    monit.wait(1.0);
    return 0;

};

