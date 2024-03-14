#ifndef looper_h_INCLUDED
#define looper_h_INCLUDED

#include <cfloat>

class Looper
{
    public:
        Looper();
        ~Looper();

    private:
        bool doStop;
        double iLoop;

    public:
        double runLoop(double nLoops = DBL_MAX);
        double getSample();
        double stopLoop();
};
#endif //looper_h