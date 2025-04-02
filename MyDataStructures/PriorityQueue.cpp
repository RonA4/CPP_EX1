//ronamsalem4@gmail.com
#include "PriorityQueue.hpp"
namespace graph {

// Constructor ---> creates an empty queue with zero size
PriorityQueue::PriorityQueue(int cap) : capacity(cap), size(0) {
    data = new Node[capacity];
}

// Destructor ---> releases memory
PriorityQueue::~PriorityQueue() {
    delete[] data;
}

// Insert a new element (vertex, distance) at the end of the array
void PriorityQueue::insert(int vertex, int distance) {
    for (int i = 0; i < size; ++i) {
        if (data[i].vertex == vertex) {
            if (distance < data[i].distance) {
                data[i].distance = distance;
            }
            return; 
        }
    }
    if (size < capacity) {
        data[size++] = {vertex, distance};
    }
}


// Returns the vertex with the smallest distance and removes it from the queue
int PriorityQueue::extractMin() {
    if (isEmpty()) return -1; // or throw error

    int minIndex = -1;
    int minValue = 1e9;

    for (int i = 0; i < size; ++i) {
        if (data[i].distance < minValue) {
            minValue = data[i].distance;
            minIndex = i;
        }
    }

    int result = data[minIndex].vertex;

    // Replace the removed element with the last element
    data[minIndex] = data[--size];

    return result;
}

// Updates the distance of a given vertex if a shorter path is found
void PriorityQueue::decreaseKey(int vertex, int newDistance) {
    for (int i = 0; i < size; ++i) {
        if (data[i].vertex == vertex && newDistance < data[i].distance) {
            data[i].distance = newDistance;
            break;
        }
    }
}

// Checks if the queue is empty
bool PriorityQueue::isEmpty() const {
    return size == 0;
}

}
