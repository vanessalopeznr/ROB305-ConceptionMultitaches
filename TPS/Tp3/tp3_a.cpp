#include <iostream>
#include "Chrono.h"
#include "time.h"

int main()
{
    bool Counter = true;
    int i = 0;
    timespec sleepMain = timespec_from_ms(1000);
    
    Chrono chrono;
    if (chrono.isActive()==0)
    {
        std::cout << " Activate Chrono " << std::endl;
    }
    
    timespec_wait(sleepMain);

    chrono.restart();
    if (chrono.isActive()==0)
    {
        std::cout << " Restart Chrono " << std::endl;
    }

    timespec_wait(sleepMain);
    std::cout << "Lap Chrono: " << chrono.lap() << std::endl;

    chrono.stop();
    std::cout << "Stop Chrono " << std::endl;
    return 0;
}
