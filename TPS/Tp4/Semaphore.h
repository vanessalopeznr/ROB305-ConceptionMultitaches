#ifndef Semaphore_h_INCLUDED
#define Semaphore_h_INCLUDED

#include "Mutex.h"
#include <climits>

class Semaphore
{
private:
	volatile unsigned int counter;
	unsigned int maxCount;
	Mutex mutex;

public:
	Semaphore(unsigned int counter = 0, unsigned int maxCount = UINT_MAX);
	~Semaphore();

public:
	void give();
	void take();
	bool take(double timeout_ms);

};

# endif // Semaphore_h
