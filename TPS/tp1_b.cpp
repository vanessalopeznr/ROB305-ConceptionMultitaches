// Executer: g++ tp1_b.cpp tp1_a.cpp tp3_b.cpp -o executable.exe

#include "Timer.h"
#include "time.h"
#include <signal.h>

int main() {
    int counter = 0;

    double duration = 500;
	PeriodicTimer test1B;

	test1B.start(duration);
	while (test1B.n <= 15)
	{
		continue;
	}
	test1B.stop();

    return 0;
}