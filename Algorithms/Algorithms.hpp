//ronamsalem4@gmail.com
#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "AdjacencyList/Graph.hpp"
#include "MyDataStructures/Queue.hpp"
#include "MyDataStructures/PriorityQueue.hpp"
#include "MyDataStructures/UnionFind.hpp"

// Graph Algorithms Statement: BFS, DFS, Dijkstra, Prim, and Kruskal.
namespace graph {

/**
 * @struct KruskalEdge
 *  Simple edge structure used in Kruskal's algorithm.
 */
    struct KruskalEdge {
        int src; // Source vertex
        int dest; // Destination vertex
        int weight; //Weight of the edge
    };
    
class Algorithms {
public:
   
    static Graph BFS(const Graph& g, int start);
    static Graph DFS(const Graph& g, int start);  
    static Graph Dijkstra(const Graph& g, int start);
     static Graph Prim(const Graph& g);
    static void sortEdges(KruskalEdge* edges, int edgeCount);
   static Graph Kruskal(const Graph& g) ;
 
};

} 
#endif
