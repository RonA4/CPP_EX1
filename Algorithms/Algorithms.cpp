//ronamsalem4@gmail.com
#include "Algorithms.hpp"
namespace graph {

enum Color { WHITE, GRAY, BLACK }; // For DFS BFS algorithms

/**
 --> BFS Algorithms <---
--------------------------------------------------
* Perform Breadth-First Search (BFS) on an undirected graph.
* This function builds a BFS tree starting from the given source vertex,
* using a simple FIFO queue. Each vertex is color-coded (white, gray, black)
* to keep track of its visit status. The resulting tree contains only pointers that we found.
* @param g ---> The undirected input graph.
* @param start ---> The starting vertex for the BFS traversal.
* @return ---> Graph A new graph representing the BFS tree rooted at 'start'.
* @throws ---> GraphError if illegal operations are performed
*/
Graph Algorithms::BFS(const Graph& g, int start) {
    int n = g.getVertexCount();
    if (start < 0 || start >= n) {
        throw GraphError("Start vertex out of bounds");
    }
    Color* color = new Color[n];
    int* distance = new int[n];
    int* parent = new int[n];

    for (int i = 0; i < n; ++i) {
        color[i] = WHITE;
        distance[i] = -1;
        parent[i] = -1;
    }
    color[start] = GRAY;
    distance[start] = 0;
    parent[start] = -1;
    Queue q(n);
    q.enqueue(start);
    while (!q.isEmpty()) {
        int u = q.dequeue();
        EdgeNode* current = g.getAdjList()[u].head;
        while (current != nullptr) {
            int v = current->destination;
            if (color[v] == WHITE) {
                color[v] = GRAY;
                distance[v] = distance[u] + 1;
                parent[v] = u;
                q.enqueue(v);
            }
            current = current->next;
        }

        color[u] = BLACK;
    }

    Graph result(n);
    for (int v = 0; v < n; ++v) {
        if (parent[v] != -1) {
            result.addEdge(parent[v], v);  
        }
    }
    delete[] color;
    delete[] distance;
    delete[] parent;
    return result;
}

 // --> DFS Algorithms <---
// --------------------------------------------------
/**
 *  recursive function for DFS.
 * Visits all reachable vertices from the given node, marking theirparent
 * and adding the corresponding edge to the DFS tree.
 * @param g ---> The input graph.
 * @param u ---> Current vertex being explored.
 * @param color ---> Array of color states for each vertex.
 * @param parent ---> Array to track each vertex's parent in the DFS tree.
 * @param result ---> The graph representing the DFS tree.
 * @param time ---> Traversal time counter (optional for timestamps).
 */
 
static void DFSVisit(const Graph& g, int u, Color* color, int* parent, Graph& result, int& time) {
    color[u] = GRAY;
    time++;
    EdgeNode* current = g.getAdjList()[u].head;
    while (current != nullptr) {
        int v = current->destination;
        if (color[v] == WHITE) {
            parent[v] = u;
            result.addEdge(u, v); 
            DFSVisit(g, v, color, parent, result, time);
        }
        current = current->next;
    }
    color[u] = BLACK;
    time++;
}
/**
 * Performs Depth-First Search (DFS) on an undirected graph.
 * The algorithm explores as far as possible along each branch before backtracking.
 * It returns a new graph containing only the tree edges discovered during DFS,
 * forming a DFS forest if the graph is disconnect
 * @param g ---> The input graph.
 * @param start --->  The starting vertex for the DFS traversal.
 * @return --->  Graph A graph containing only tree edges from the DFS.
 */
Graph Algorithms::DFS(const Graph& g, int start) {
    int n = g.getVertexCount();
    Color* color = new Color[n];
    int* parent = new int[n];
    for (int i = 0; i < n; ++i) {
        color[i] = WHITE;
        parent[i] = -1;
    }
    int time = 0;
    Graph result(n);

    if (color[start] == WHITE) {
        DFSVisit(g, start, color, parent, result, time);
    }
    for (int u = 0; u < n; ++u) {
        if (color[u] == WHITE) {
            DFSVisit(g, u, color, parent, result, time);
        }
    }
    delete[] color;
    delete[] parent;
    return result;
}

/*
---> Dijkstra Algorithms <---
--------------------------------------------------
* This function implements Dijkstra's Algorithm to compute the shortest paths from a given source vertex to all other vertices in a directed and weighted graph
* The input graph does not contain any negative weight edges. The algorithm constructs a shortest path tree
* Parameters:
* const Graph& g : The input graph to run the algorithm on.
* int start : The index of the starting vertex.
* Throws:
* GraphError if any edge has a negative weight or if invalid vertex indices are encountered.
* Implementation details:
* dist[] : Stores the shortest known distances from the start to each vertex.
* parent[] : Stores the parent of each vertex in the shortest path tree.
* Visited[]: Marks whether a vertex is complete (its shortest path is known).
* PriorityQueue is used to extract the next vertex with the minimum tentative distance.
*/
Graph Algorithms::Dijkstra(const Graph& g, int start) {
    int n = g.getVertexCount();
    for (int i = 0; i < n; ++i) {
        EdgeNode* current = g.getAdjList()[i].head;
        while (current != nullptr) {
            if (current->weight < 0) {
                throw GraphError("Dijkstra does not support negative edge weights");
            }
            current = current->next;
        }
    }

    int* dist = new int[n];     
    int* parent = new int[n];    
    bool* visited = new bool[n];  
    for (int i = 0; i < n; ++i) {
        dist[i] = 1e9;   
        parent[i] = -1;
        visited[i] = false;
    }

    dist[start] = 0;
    PriorityQueue pq(n);
    pq.insert(start, 0);

    while (!pq.isEmpty()) {
        int u = pq.extractMin();
        if (visited[u]) continue;
        visited[u] = true;

        EdgeNode* edge = g.getAdjList()[u].head;
        while (edge != nullptr) {
            int v = edge->destination;
            int w = edge->weight;
            if (!visited[v] && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.decreaseKey(v, dist[v]);
                pq.insert(v, dist[v]);
            }
            edge = edge->next;
        }
    }

    Graph result(n);
    for (int v = 0; v < n; ++v) {
        if (parent[v] != -1) {
            int u = parent[v];
            int weight = dist[v] - dist[u];

            if (u < v) {
                result.addEdge(u, v, weight);
            } else {
                result.addEdge(v, u, weight);
            }
        }
    }

    delete[] dist;
    delete[] parent;
    delete[] visited;
    return result;
}


/**
---> Prim Algorithms <---
--------------------------------------------------
* Computes the Minimum Spanning Tree (MST) of an undirected weighted graph using Prim's algorithm.
* The function starts at vertex 0 and gradually builds the MST by choosing the minimum edge
* The minimum weight edge connecting a vertex inside the tree to a vertex outside.
* A priority queue to keep track of the nearest vertex that is not included.
* @param g ---> The undirected input graph with positive edge weights.
* @return ---> Graph A new graph representing the MST with the same set of vertices and a subset of edges.
* @throws ---> GraphError if the priority queue operation fails.
*/
Graph Algorithms::Prim(const Graph& g) {
    int n = g.getVertexCount();
    int* key = new int[n];        
    int* parent = new int[n];     
    bool* inMST = new bool[n];    
    for (int i = 0; i < n; ++i) {
        key[i] = 1e9;
        parent[i] = -1;
        inMST[i] = false;
    }

    key[0] = 0;

    PriorityQueue pq(n);
    pq.insert(0, 0);  

    while (!pq.isEmpty()) {
        int u = pq.extractMin();
        if (inMST[u]) continue;
        inMST[u] = true;

        EdgeNode* edge = g.getAdjList()[u].head;
        while (edge != nullptr) {
            int v = edge->destination;
            int w = edge->weight;

            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
                pq.insert(v, w); 
            }

            edge = edge->next;
        }
    }
    Graph mst(n);
    for (int v = 1; v < n; ++v) {
        int u = parent[v];
        if (u != -1) {
            mst.addEdge(u, v, key[v]);
        }
    }
    delete[] key;
    delete[] parent;
    delete[] inMST;
    return mst;
}


//---> Kruskal Algorithms <---
//--------------------------------------------------

/*
 * Sorts an array of edges in ascending order by weight.
 * This function implements a simple selection sort algorithm to sort
 *  It compares the weight of and arranges them from smallest to largest.
 * @param edges Pointer to an array of KruskalEdge structures.
 * @param edgeCount The number of edges in the array.
*/

void Algorithms::sortEdges(KruskalEdge* edges, int edgeCount) {
    for (int i = 0; i < edgeCount - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < edgeCount; ++j) {
            if (edges[j].weight < edges[minIndex].weight) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            KruskalEdge temp = edges[i];
            edges[i] = edges[minIndex];
            edges[minIndex] = temp;
        }
    }
}

/**
*Computes the minimum spanning tree (MST) of an undirected weighted graph using Kruskal's algorithm.
* The function collects all edges, sorts them in ascending order by weight,
* and iteratively adds the smallest edge that does not create a cycle,
* Using the Union-Find data structure to manage connected components.
* @param g The undirected input graph with positive edge weights.
* @return Graph A new graph representing the MST.
* @throws GraphError if the graph structure is invalid.
*/
Graph Algorithms::Kruskal(const Graph& g) {
    int n = g.getVertexCount();
    int maxEdges = 0;
    for (int u = 0; u < n; ++u) {
        EdgeNode* current = g.getAdjList()[u].head;
        while (current != nullptr) {
            ++maxEdges;
            current = current->next;
        }
    }
    KruskalEdge* edges = new KruskalEdge[maxEdges];
    int edgeIndex = 0;
    bool** added = new bool*[n]; 
    for (int i = 0; i < n; ++i) {
        added[i] = new bool[n];
        for (int j = 0; j < n; ++j) added[i][j] = false;
    }

    for (int u = 0; u < n; ++u) {
        EdgeNode* current = g.getAdjList()[u].head;
        while (current != nullptr) {
            int v = current->destination;
            int w = current->weight;
            if (!added[u][v] && !added[v][u]) {
                edges[edgeIndex++] = {u, v, w};
                added[u][v] = added[v][u] = true;
            }
            current = current->next;
        }
    }
    sortEdges(edges, edgeIndex); 
    Graph mst(n);
    UnionFind uf(n);
    int edgesUsed = 0;

    for (int i = 0; i < edgeIndex && edgesUsed < n - 1; ++i) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int w = edges[i].weight;

        if (uf.find(u) != uf.find(v)) {
            uf.unite(u, v);
            mst.addEdge(u, v, w);  
            ++edgesUsed;
        }
    }

    for (int i = 0; i < n; ++i) delete[] added[i];
    delete[] added;
    delete[] edges;
    return mst;
}
} 



