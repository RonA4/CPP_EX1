//ronamsalem4@gmail.com
#include "Queue.hpp"
#include "GraphError.hpp"  

namespace graph {

/**
 * Constructs a new Queue with a fixed capacity.
 * @param cap ---> The maximum number of elements the queue can hold.
 */

Queue::Queue(int cap) : capacity(cap), front(0), rear(0), size(0) {
    data = new int[capacity];
}

/** 
* Destructor that releases the dynamically allocated memory.
*/
Queue::~Queue() {
    delete[] data;
}

/**
 * Inserts a new value at the rear of the queue. 
 * @param value ---> The integer to enqueue.
 * @throws --->  GraphError if the queue is full.
 */
void Queue::enqueue(int value) {
    if (size == capacity) {
        throw GraphError("Queue is full");
    }
    data[rear] = value;
    rear = (rear + 1) % capacity;
    ++ size;
}
/**
 *Removes and returns the front value from the queue.
 * @return ---> int The value at the front.
 * @throws ---> GraphError if the queue is empty.
 */
int Queue::dequeue() {
    if (isEmpty()) {
        throw GraphError("Queue is empty");
    }
    int val = data[front];
    front = (front + 1) % capacity;
    --size;
    return val;
}

/**
 * Checks if the queue is empty. 
 * @return ---> true If the queue contains no elements, false Otherwise.
 */
bool Queue::isEmpty() const {
    return size == 0;
}

} 
