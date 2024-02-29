#ifndef Calibrator_h_INCLUDED
#define Calibrator_h_INCLUDED

#include <pthread.h>
#include <time.h>
#include <vector>
#include "Timer.h"
#include "Looper.h"

class Calibrator : public PeriodicTimer
{
    private:
        double a;
        double b;
        std::vector<double> samples;
        Looper myLooper;
        unsigned nSamples;
    
    public:
        Calibrator(double samplingPeriod_ms, unsigned nSamples);
        double nLoops(double duration_ms);

    protected:
        virtual void callback() override;
};

#endif