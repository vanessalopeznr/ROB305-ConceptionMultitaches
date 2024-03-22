// [TD3-a]

#include "Chrono.h"
#include <time.h>
#include "time.h"

Chrono::Chrono() : m_stopTime(timespec_now())
{
    restart();
}

void Chrono::restart()
{
    m_startTime = timespec_now();
}

void Chrono::stop()
{
    m_stopTime = timespec_now();
}

bool Chrono::isActive()
{
    if (m_startTime == m_stopTime)
    {
        return true;
    }
    else
    {
        return false;
    }
}

double Chrono::lap()
{
    if (isActive())
    {
        timespec currentTime = timespec_now();
        return timespec_to_ms(currentTime-m_startTime);
    }
    else
    {
        return timespec_to_ms(m_stopTime-m_startTime);
    }
}