//[TD3-c]

#include "CpuLoop.h"
#include "Calibrator.h"

CpuLoop::CpuLoop(Calibrator& calibrator) : Looper(), calib(calibrator){}

void CpuLoop::runTime(double duration_ms)
{
    runLoop(calib.nLoops(duration_ms));
}