//ronamsalem4@gmail.com
#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP
namespace graph {
// A basic priority queue implementation used for graph algorithms such as Dijkstra and Prim.
class PriorityQueue {
private:
    struct Node {
        int vertex;
        int distance;
    };

    Node* data; // Array to hold queue elements
    int capacity; // Maximum number of elements
    int size;// Current number of elements

public:
    PriorityQueue(int cap);
    ~PriorityQueue();
    void insert(int vertex, int distance);
    int extractMin();
    void decreaseKey(int vertex, int newDistance);
    bool isEmpty() const;
};
}
#endif
