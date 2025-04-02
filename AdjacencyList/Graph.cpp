//ronamsalem4@gmail.com
#include "Graph.hpp"
#include "GraphError.hpp"  
namespace graph {
/**
 * Constructs a graph with the given number of vertices.
 * Initializes an empty adjacency list for each vertex.
 * @param vertices ---> Number of vertices in the graph.
 */
Graph::Graph(int vertices) : numVertices(vertices) {
    adjacencyList = new VertexNode[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        adjacencyList[i].vertexNumber = i;
        adjacencyList[i].head = nullptr;
    }
}
/**
 *Destructor that frees all allocated memory for the adjacency list.
 */
Graph::~Graph() {
    for (int i = 0; i < numVertices; ++i) {
        EdgeNode* current = adjacencyList[i].head;
        while (current != nullptr) {
            EdgeNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adjacencyList;
}
/**
 * Adds a directed edge from source to destination with a given weight.
 * @param source ---> Source vertex.
 * @param destination ---> Destination vertex.
 * @param weight ---> Weight of the edge.
 * @throws ---> GraphError if source or destination is out of bounds.
 */
void Graph::addEdge(int source, int destination, int weight) {
    if (source < 0 || source >= numVertices || destination < 0 || destination >= numVertices) {
        throw GraphError("Index out of bounds in addEdge");
    }

    EdgeNode* newNode1 = new EdgeNode(destination, weight, adjacencyList[source].head);
    adjacencyList[source].head = newNode1;

    EdgeNode* newNode2 = new EdgeNode(source, weight, adjacencyList[destination].head);
    adjacencyList[destination].head = newNode2;
}

/**
 * Removes the directed edge from source to destination.
 * @param source ---> Source vertex.
 * @param destination ---> Destination vertex.
 * @throws ---> GraphError if source or destination is out of bounds or edge does not exist.
 */
void Graph::removeEdge(int source, int destination) {
    if (source < 0 || source >= numVertices || destination < 0 || destination >= numVertices) {
        throw GraphError("Index out of bounds in removeEdge");
    }
    bool removed = false;
    EdgeNode* current = adjacencyList[source].head;
    EdgeNode* prev = nullptr;
    while (current != nullptr) {
        if (current->destination == destination) {
            if (prev == nullptr) {
                adjacencyList[source].head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            removed = true;
            break;
        }
        prev = current;
        current = current->next;
    }

    current = adjacencyList[destination].head;
    prev = nullptr;
    while (current != nullptr) {
        if (current->destination == source) {
            if (prev == nullptr) {
                adjacencyList[destination].head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!removed) {
        throw GraphError("Edge does not exist");
    }
}

/**
 * Prints the adjacency list of the graph to the standard output.
 */
void Graph::printGraph() const {
    for (int i = 0; i < numVertices; ++i) {
        std::cout << "Vertex " << adjacencyList[i].vertexNumber << " -> ";
        EdgeNode* current = adjacencyList[i].head;
        while (current != nullptr) {
            std::cout << "(" << current->destination << ", weight: " << current->weight << ") ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}
/**
 * Returns the total number of vertices in the graph.
 * @return  ---> int Number of vertices.
 */
int Graph::getVertexCount() const {
    return numVertices;
}

/**
 *  Returns the internal adjacency list pointer.
 * @return ---> VertexNode* Pointer to the adjacency list array.
 */
VertexNode* Graph::getAdjList() const {
    return adjacencyList;
}


}
