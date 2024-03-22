// Executer: g++ tp4_a.cpp PosixThread.cpp time.cpp -o executable.exe


#include <iostream>
#include "PosixThread.h"

struct Data {
    volatile bool stop;
    volatile int counter;
};

class IncrementerThread : public Thread {
private:
    Data* data;

public:
    IncrementerThread(Data* data) : data(data) {}

protected:
    void run() override {
        while (!data->stop) {
            data->counter += 1;
        }
    }
};

int main() {
    Data data = { false, 0 };

    IncrementerThread incrementThread(&data);
    incrementThread.start();

    for (char cmd = 'r'; cmd != 's'; std::cin >> cmd)
        std::cout << "Type 's' to stop: " << std::flush;

    data.stop = true;
    
    incrementThread.join();

    std::cout << "Counter value = " << data.counter << std::endl;
    return 0;
}

