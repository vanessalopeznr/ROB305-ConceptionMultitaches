// Executer: g++ tp4_c.cpp Semaphore.cpp PosixThread.cpp Mutex.cpp -o executable.exe

#include <iostream>
#include <vector>
#include "Semaphore.h"
#include "PosixThread.h"
#include <memory>


class ProducerTask : public Thread
{
private:
    Semaphore &semaphore;
public:
    ProducerTask(Semaphore &semaphore) : semaphore(semaphore) {}
    void run(){semaphore.give();}
};


class ConsumerTask : public Thread
{
private:
    Semaphore &semaphore;
public:
    ConsumerTask(Semaphore &semaphore) : semaphore(semaphore) {}
    void run() {semaphore.take();}
};


// Function to create producer tasks
std::vector<std::unique_ptr<Thread>> createProducers(int nProd, Semaphore& semaphore)
{
    std::vector<std::unique_ptr<Thread>> threads;
    for (int i = 0; i < nProd; i++)
    {
        threads.push_back(std::make_unique<ProducerTask>(semaphore));
    }
    return threads;
}

// Function to create consumer tasks
std::vector<std::unique_ptr<Thread>> createConsumers(int nCons, Semaphore& semaphore)
{
    std::vector<std::unique_ptr<Thread>> threads;
    for (int i = 0; i < nCons; i++) 
    {
        threads.push_back(std::make_unique<ConsumerTask>(semaphore));
    }
    return threads;
}

int main()
{
    // Number of consumers and producers
    int nProd = 3;
    int nCons = 2;

    // Create the Semaphore
    Semaphore semaphore(0);

    // Create producer and consumer tasks
    auto producerTasks = createProducers(nProd, semaphore);
    auto consumerTasks = createConsumers(nCons, semaphore);

    // Start all tasks
    for (auto& task : producerTasks) {
        task->start();
    }

    for (auto& task : consumerTasks) {
        task->start();
    }

    // Join all tasks
    for (auto& task : producerTasks) {
        task->join();
    }

    for (auto& task : consumerTasks) {
        task->join();
    }

    return 0;
}
