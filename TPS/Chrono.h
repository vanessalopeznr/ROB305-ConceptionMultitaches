#ifndef Chrono_INCLUDED
#define Chrono_INCLUDED

#include <time.h>

class Chrono
{
    private:
        timespec m_startTime;
        timespec m_stopTime;
    
    public:
        Chrono();
        void stop();
        void restart();
        bool isActive();
        double lap();
};

#endif