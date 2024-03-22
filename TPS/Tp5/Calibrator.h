#ifndef Calibrator_h_INCLUDED
#define Calibrator_h_INCLUDED

#include <pthread.h>
#include <time.h>
#include <vector>
#include "Timer.h"
#include "Looper.h"

class Calibrator : public Timer
{
    private:
        double a;
        double b;
        std::vector<double> samples;
        Looper looper;
        unsigned nSamples;
    
    public:
        Calibrator(double samplingPeriod_ms, unsigned nSamples);
        double nLoops(double duration_ms);

    protected:
        // Override for make sure over ride the same method in Timer
        virtual void callback() override;
};

#endif