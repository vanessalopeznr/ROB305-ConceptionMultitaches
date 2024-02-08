#include "PosixThread.h"

// Pas inicialise dans les blocks
PosixThread::PosixThread(): posixId(0), isActive(false)
{
    pthread_attr_init(&posixId);
}

PosixThread::PosixThread(pthread_t posixId): posixId(posixId), isActive(false)
{
    pthread_attr_init(&posixId);
    int schedPolicy;
    schedparam schedp;
    if (pthread_getschedparam(posixId, &schedPolicy, &schedp)<0)
    {
        isActive = false;
        posixId = 0;
    }
    pthread_attr_setschedparam(&posixAttr, schedPolicy);
    pthread_attr_setschedparam(&posixAttr, &schedp);
}