#ifndef Fifo_hpp_INCLUDED
#define Fifo_hpp_INCLUDED

#include "Mutex.h"
#include <queue>
#include <exception>
#include <string>
#include "time.h"

template<typename T>
class Fifo
{
    public:
        Fifo(): mutex() {}
        ~Fifo() {}

    public:
        class EmptyException : public std::exception 
        {
        public:
            const char* what() const noexcept 
            {
                return "Exception: Empty Queue";
            }
        };

        void push(T element)
        {
            Mutex::Lock lock(mutex);
            elements.push(element);
            lock.notifyAll();
        };

        T pop()
        {
            Mutex::Lock lock(mutex);

            while (elements.empty())
            {
                lock.wait();
            }
            
            T element = elements.front();
            elements.pop();
            lock.notifyAll();
            return element;
        }

        T pop(double timeout_ms)
        {
            Mutex::Lock lock(mutex, timeout_ms); 
            if (elements.empty())  
            {
                if (lock.wait(timeout_ms))
                {
                    throw EmptyException();
                }
            }
            T element = elements.front();
            elements.pop();
            return element;
        }

    size_t size()
    {
        Mutex::Lock lck(mutex);
        return elements.size();
    }



    
    private:
        std::queue<T> elements;
        Mutex mutex;

    
};
#endif