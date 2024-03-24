// Executer: g++ tp1_b.cpp time.cpp Timer.cpp -o executable.exe

#include "Timer.h"
#include "time.h"
#include <signal.h>

using namespace std;

class PeriodicTimer : public Timer
{
	public :
        volatile int n = 0; 

	protected:
		void callback()
		{
			cout << "Compteur: " << this -> n << endl;
			(this -> n)++;
		}
};


int main() {
    int counter = 0;

    double duration = 500;
	
	PeriodicTimer test1B;

	test1B.start(duration, true);
	while (test1B.n <= 15)
	{
		continue;
	}
	test1B.stop();

	cout << "Fini ! :)";
	
    return 0;
}