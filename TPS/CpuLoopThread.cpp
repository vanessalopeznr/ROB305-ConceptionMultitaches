#include "CpuLoopThread.h"
#include "CpuLoop.h"
#include "Mutex.h"
#include "Calibrator.h"
#include <time.h>

CpuLoopThread::CpuLoopThread(Mutex& mutex, CpuLoop& cpuLoop):Thread(), mutex(mutex), cpuLoop(cpuLoop) {}

CpuLoopThread::~CpuLoopThread() {}