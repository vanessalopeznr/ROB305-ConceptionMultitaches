//[TD3-c]

#include <iostream>
#include "Calibrator.h"
#include "Looper.h"

Calibrator::Calibrator(double samplingPeriod_ms, unsigned nSamples) : nSamples(nSamples) 
{
    std::cout << "Inicializing calibrator constructor..." << std::endl;
    start(samplingPeriod_ms,true); //Start Timer
    looper.runLoop();
    stop();

    double sumX=0, sumXX=0, sumY=0, sumXY=0;

    for (unsigned i = 0; i < nSamples; i++)
    {
        sumX  += samplingPeriod_ms*i;
        sumXX += (samplingPeriod_ms*i)*(samplingPeriod_ms*i);
        sumY  += samples[i];
        sumXY += (samplingPeriod_ms*i)*samples[i];
    }

    a = (sumXY-sumX*sumY/nSamples)/(sumXX - (sumX*sumX)/nSamples);
    b = (sumXX*sumY - sumXY*sumX)/(nSamples*sumXX - sumX*sumX);
}

double Calibrator::nLoops(double duration_ms)
{
    return (a*duration_ms+b);
}

void Calibrator::callback()
{
    double sample = looper.getSample();
    samples.push_back(sample);

    if (samples.size() == nSamples)
    {
        looper.stopLoop();
    }

}
