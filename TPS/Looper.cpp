//[TD3-c]

#include "Looper.h"

Looper::Looper(){}

Looper::~Looper(){}

double Looper::runLoop(double nLoops)
{
    doStop = false;
    while (iLoop < nLoops && doStop == false)
    {
        iLoop += 1.0 ;
    }
    return iLoop;
}

double Looper::getSample()
{
    return iLoop;
}

double Looper::stopLoop()
{
    doStop = true;
    return iLoop;
}