#include <iostream>
#include "Timer.h"
#include "time.h"


class CountDown : public Timer
{
private:
    int nCount;

protected:
    void callback() override;

public:
    CountDown(int n);
    int get_nCount();
};

CountDown::CountDown(int n)
{
    nCount = n;
}

void CountDown::callback()
{
    if (nCount > 0)
    {
        std::cout << "Count: " << nCount << std::endl;
        --nCount;
    }
    else
    {
        stop();
    }
}

int CountDown::get_nCount()
{
    return nCount;
}


int main()
{

    CountDown count(20);
    count.start(500, true);
    timespec sleepMain = timespec_from_ms(20);
    
    // Do another thing
    while (count.get_nCount() > 0)
    {
        timespec_wait(sleepMain);
    }

    return 0;
}

