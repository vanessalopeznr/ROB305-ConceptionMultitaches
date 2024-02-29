#ifndef CpuLoop_h_INCLUDED
#define CpuLoop_h_INCLUDED

#include "Looper.h"
#include "Calibrator.h"

class CpuLoop : public Looper
{
    private:
        Calibrator& calib;

    public:
        CpuLoop(Calibrator& calibrator);
        void runTime(double duration_ms);
};

#endif
