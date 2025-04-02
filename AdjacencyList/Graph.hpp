//ronamsalem4@gmail.com
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include "GraphError.hpp" 

namespace graph {

    
/**
 *  Represents a node in the adjacency list (an edge).
 */
    struct EdgeNode {
        int destination;
        int weight;
        EdgeNode* next;

     /**
     * Constructs an EdgeNode.
     * @param dest ---> Destination vertex.
     * @param w ---> Weight of the edge.
     * @param n  ---> Pointer to the next edge node.
     */
        EdgeNode(int dest, int w, EdgeNode* nxt = nullptr)
            : destination(dest), weight(w), next(nxt) {}
    };

    
/**
 * Represents a vertex in the graph, containing its adjacency list.
 */
    struct VertexNode {
        int vertexNumber;
        EdgeNode* head;
    
        VertexNode() : vertexNumber(-1), head(nullptr) {}
    };
/**
 * Class representing a directed, weighted graph using an adjacency list.
 */
    class Graph {
    private:
        int numVertices;
        VertexNode* adjacencyList;

    public:
        Graph(int vertices);
        ~Graph();

        void addEdge(int source, int destination, int weight = 1);
        void removeEdge(int source, int destination);
        void printGraph() const;
        int getVertexCount() const;
        VertexNode* getAdjList() const;
    };

}

#endif
