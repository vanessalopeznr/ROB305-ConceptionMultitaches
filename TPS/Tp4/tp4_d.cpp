// Executer: g++ tp4_d.cpp PosixThread.cpp Mutex.cpp time.cpp -o executable.exe


#include "Fifo.h"
#include "PosixThread.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class ProducerFifoThread : public Thread 
    {
    public:
        ProducerFifoThread(Fifo<int>* fifo, int nElem ) :  fifo(fifo), nElements(nElem) {}
        ~ProducerFifoThread() {}

    private:
        Fifo<int>* fifo;
    
    public:
        int nElements; 
        void run() 
        {
            for (int i = 0; i < nElements; i++)
            {
                fifo->push(i);
            }
        }
    };


class ConsumerFifoThread : public Thread 
{
    public:
        ConsumerFifoThread(Fifo<int>* fifo, int producerSize) : fifo(fifo), nElements(producerSize), iElement(0) {}
        ~ConsumerFifoThread() {}

    private:
        int nElements; 
        Fifo<int>* fifo;
        
    public:  
        int iElement;  
        void run() 
        {
            int max = nElements;
            for (int i = 0; i < max; i++)
            {
                int element = fifo->pop();
                iElement++;
            }
        }
};


int main(int argc, char const *argv[])
{
    int nElements = 3;

    Fifo<int> fifo;
    
    ConsumerFifoThread consumer(&fifo, nElements);

    ProducerFifoThread producer(&fifo, nElements);

    consumer.start();
    producer.start();

    producer.join();
    consumer.join();

    std::cout << "[Consumer] count: " << consumer.iElement << std::endl;


    return 0;
}