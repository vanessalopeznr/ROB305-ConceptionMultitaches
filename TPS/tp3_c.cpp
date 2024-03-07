// Executer: g++ tp3_c.cpp Calibrator.cpp Looper.cpp CpuLoop.cpp Chrono.cpp Timer.cpp time.cpp -o executable.exe
#include "Looper.h"
#include "Calibrator.h"
#include "CpuLoop.h"
#include "Chrono.h"
#include <iostream>

int main(){

    double estimatedTime =  2000.0;
    double calibrationTime = 100.0;

    Calibrator calibrator(calibrationTime,10);

    CpuLoop cpuLoop(calibrator);
    Chrono chrono;
    cpuLoop.runTime(estimatedTime);
    chrono.stop();
    double realTime = chrono.lap();

    double accuracy = (realTime-estimatedTime)*100/estimatedTime;

    std::cout << "Estimated time " << estimatedTime << " ms, real time " << realTime << " ms" << std::endl;
    std::cout << "Accuracy " << accuracy << " %" << std::endl;

    return 0;

};