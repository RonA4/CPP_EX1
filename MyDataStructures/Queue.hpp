//ronamsalem4@gmail.com
#ifndef QUEUE_H
#define QUEUE_H


namespace graph {

/**
* Class Queue ---> DFS and BFS algorithms
* Implements a basic FIFO queue with fixed capacity, using circular buffer logic.
*/
class Queue {
private:
    int* data;  // Dynamic array to hold queue elements
    int front;  //  Index of the front element
    int rear;  // Index of the next insertion point
    int capacity; // Maximum number of elements the queue can hold
    int size; // Current number of elements in the queue

public:
    Queue(int cap); // Constructor to initialize the queue with a given capacity.
    ~Queue();// Destructor to release the allocated memory.

    void enqueue(int value); // Inserts a new value at the rear of the queue.
    int dequeue();//Removes and returns the front value from the queue.
    bool isEmpty() const;// Checks whether the queue is empty.
};

} 

#endif
