#ifndef QUEUE_FACTORY_HPP
#define QUEUE_FACTORY_HPP

#include "ArrayQueue.hpp"
#include "LinkedQueue.hpp"

// Factory class that decides which queue type to create
class QueueFactory {
public:
    // Returns a pointer to a Queue<T> object
    // If a positive size is specified → returns an ArrayQueue<T>
    // If no size (or <= 0) → returns a LinkedQueue<T>
    template <typename T>
    static Queue<T>* GetQueue(int maxSize = 0) {
        if (maxSize > 0)
            return new ArrayQueue<T>(maxSize);  // bounded, circular queue
        else
            return new LinkedQueue<T>();        // unbounded, linked queue
    }
};

#endif
