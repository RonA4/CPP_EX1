//ronamsalem4@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Algorithms/Algorithms.hpp"  
#include "AdjacencyList/Graph.hpp"
#include "TestAndException/GraphError.hpp"


using namespace graph;

TEST_CASE ("Removing an edge that does not exist in a graph"){
    Graph g(4);
    g.addEdge(0,1,1);
    g.addEdge(0,2,4);
    g.addEdge(1,2,2);
    g.addEdge(2,3,3);
    g.removeEdge(0,1);
    CHECK_THROWS_AS( g.removeEdge(0,1), GraphError);
}

TEST_CASE("Adding an edge with a negative vertex index throws exception") {
    Graph g(3);
    
    CHECK_THROWS_AS(g.addEdge(-1, 2, 5), GraphError);  
    CHECK_THROWS_AS(g.addEdge(1, -2, 5), GraphError); 
}

TEST_CASE("Return the current number of vertices") {
    Graph g(4);
    CHECK(g.getVertexCount() == 4);
}
 // Test for checking Data Structures ---> Prioity Queue , Queue, Union Find 
// -----------Test -  Prioity Queue------------------
TEST_CASE("PriorityQueue basic insert and extract") {
    PriorityQueue pq(10);

    pq.insert(0, 50);
    pq.insert(1, 30);
    pq.insert(2, 40);

    CHECK(pq.extractMin() == 1); 
    CHECK(pq.extractMin() == 2); 
    CHECK(pq.extractMin() == 0);
    CHECK(pq.isEmpty() == true);
}

TEST_CASE("PriorityQueue handles decreaseKey correctly via insert") {
    PriorityQueue pq(10);

    pq.insert(0, 50);
    pq.insert(1, 30);
    pq.insert(0, 20); 
    CHECK(pq.extractMin() == 0); 
    CHECK(pq.extractMin() == 1); 
    CHECK(pq.isEmpty() == true);
}

TEST_CASE("PriorityQueue avoids duplicates") {
    PriorityQueue pq(5);
    pq.insert(0, 50);
    pq.insert(0, 60); 
    pq.insert(0, 40); 
    CHECK(pq.extractMin() == 0);
    CHECK(pq.isEmpty() == true);
}

TEST_CASE("PriorityQueue decreaseKey function works explicitly") {
    PriorityQueue pq(3);
    pq.insert(0, 100);
    pq.insert(1, 90);
    pq.insert(2, 80);
    pq.decreaseKey(0, 70); 
    CHECK(pq.extractMin() == 0); 
    CHECK(pq.extractMin() == 2);
    CHECK(pq.extractMin() == 1);
    CHECK(pq.isEmpty() == true);
}

TEST_CASE("PriorityQueue handles empty extract") {
    PriorityQueue pq(2);
    CHECK(pq.extractMin() == -1); 
    CHECK(pq.isEmpty() == true);
}
// -----------Test -  Queue------------------
TEST_CASE("Queue basic enqueue and dequeue") {
    Queue q(3);
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    CHECK(q.dequeue() == 10);
    CHECK(q.dequeue() == 20);
    CHECK(q.dequeue() == 30);
    CHECK(q.isEmpty() == true);
}

TEST_CASE("Queue throws when full") {
    Queue q(2);
    q.enqueue(1);
    q.enqueue(2);
    CHECK_THROWS_AS(q.enqueue(3), GraphError); 
}

TEST_CASE("Queue throws when empty") {
    Queue q(2);
    CHECK_THROWS_AS(q.dequeue(), GraphError);  
}

TEST_CASE("Queue wraps around correctly ") {
    Queue q(3);
    q.enqueue(1);
    q.enqueue(2);
    CHECK(q.dequeue() == 1);
    CHECK(q.dequeue() == 2);
    q.enqueue(3);
    q.enqueue(4);
    CHECK(q.dequeue() == 3);
    CHECK(q.dequeue() == 4);
    CHECK(q.isEmpty() == true);
}
// -----------Test - Union find------------------

TEST_CASE("UnionFind basic functionality") {
    UnionFind uf(5);

    for (int i = 0; i < 5; ++i) {
        CHECK(uf.find(i) == i);
    }
    uf.unite(0, 1);
    CHECK(uf.find(0) == uf.find(1));

    uf.unite(2, 3);
    CHECK(uf.find(2) == uf.find(3));

    uf.unite(1, 3); 
    CHECK(uf.find(0) == uf.find(3));
}

TEST_CASE("UnionFind does not merge already connected components") {
    UnionFind uf(3);
    uf.unite(0, 1);
    uf.unite(1, 2);

    int rootBefore = uf.find(0);
    uf.unite(0, 2); 
    int rootAfter = uf.find(0);

    CHECK(rootBefore == rootAfter);
}

TEST_CASE("UnionFind large chain with path compression") {
    UnionFind uf(10);
    for (int i = 0; i < 9; ++i) {
        uf.unite(i, i + 1);
    }

    int root = uf.find(0);
    for (int i = 1; i < 10; ++i) {
        CHECK(uf.find(i) == root);
    }
}

//Tests for checking algorithms ---> BFS , DFS , Dijkstra , Prim , Kruskal

// -----------Test - Bfs ------------------
TEST_CASE("BFS excludes unreachable nodes from the result tree") {
    Graph g(6);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);
    Graph tree = Algorithms::BFS(g, 0);
    CHECK(tree.getAdjList()[4].head == nullptr);
    CHECK(tree.getAdjList()[5].head == nullptr);
}

TEST_CASE("BFS excludes unreachable nodes from the result tree") {
    Graph g(6);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);
   

    Graph tree = Algorithms::BFS(g, 0);

    CHECK(tree.getAdjList()[4].head == nullptr);
    CHECK(tree.getAdjList()[5].head == nullptr);
}


TEST_CASE("BFS returns correct structure - checks edges, not parent") {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 3, 1);
    g.addEdge(0, 4, 1);
    g.addEdge(3, 2, 1);
    g.addEdge(1, 2, 1);
    Graph tree = Algorithms::BFS(g, 0);
    int edgeCount = 0;
    for (int u = 0; u < tree.getVertexCount(); ++u) {
        EdgeNode* curr = tree.getAdjList()[u].head;
        while (curr) {
            edgeCount++;
            curr = curr->next;
        }
    }
    CHECK(edgeCount / 2 == 4);
    CHECK(tree.getAdjList()[0].head != nullptr);
    bool visited[5] = {false};
    for (int u = 0; u < 5; ++u) {
        EdgeNode* curr = tree.getAdjList()[u].head;
        while (curr) {
            visited[curr->destination] = true;
            curr = curr->next;
        }
    }
    for (int i = 1; i < 5; ++i) {
        CHECK(visited[i]);
    }
}

// -----------Test - Dfs ------------------



TEST_CASE("DFS returns correct number of edges and connectivity") {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 1);
    Graph tree = Algorithms::DFS(g, 0);
    int edgeCount = 0;
    for (int u = 0; u < tree.getVertexCount(); ++u) {
        EdgeNode* curr = tree.getAdjList()[u].head;
        while (curr) {
            edgeCount++;
            curr = curr->next;
        }
    }
    CHECK(edgeCount / 2 == 4); // n-1 edges
    for (int u = 0; u < 5; ++u) {
        CHECK(tree.getAdjList()[u].head != nullptr);
    }
}

// ----------------Test - Dijkstra --------------
TEST_CASE("Dijkstra leaves unreachable nodes at infinity") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    Graph result = Algorithms::Dijkstra(g, 0);
    int connectedCount = 0;
    for (int u = 0; u < 4; ++u) {
        if (result.getAdjList()[u].head != nullptr)
            connectedCount++;
    }
    CHECK(connectedCount == 2);
}

TEST_CASE("Dijkstra returns a valid tree with correct number of edges") {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);
    Graph tree = Algorithms::Dijkstra(g, 0);
    int edgeCount = 0;
    for (int u = 0; u < tree.getVertexCount(); ++u) {
        EdgeNode* curr = tree.getAdjList()[u].head;
        while (curr) {
            edgeCount++;
            curr = curr->next;
        }
    }
    CHECK(edgeCount / 2 == 3);
}

TEST_CASE("Checking for edges with negative weight in a graph"){
    Graph g(3);
    g.addEdge(0,1,10);
    g.addEdge(0,2,5);
    g.addEdge(2,1,-4);
    CHECK_THROWS_AS(Algorithms::Dijkstra(g,0);, GraphError); 
}

TEST_CASE("Dijkstra on graph with single node and no edges") {
    Graph g(1); 
    CHECK_NOTHROW(Algorithms::Dijkstra(g, 0));
}

TEST_CASE("Dijkstra handles self-loop correctly") {
    Graph g(2);
    g.addEdge(0, 0, 10);  
    g.addEdge(0, 1, 5);
    CHECK_NOTHROW(Algorithms::Dijkstra(g, 0));
}
// ----------------Test - Prim--------------

TEST_CASE("Prim returns correct MST with minimum weight") {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    Graph mst = Algorithms::Prim(g);

    int totalWeight = 0;
    for (int u = 0; u < mst.getVertexCount(); ++u) {
        EdgeNode* curr = mst.getAdjList()[u].head;
        while (curr) {
            totalWeight += curr->weight;
            curr = curr->next;
        }
    }

    CHECK(totalWeight / 2 == 19);
}

TEST_CASE("Prim's Algorithm on a basic graph") {
    Graph g(5);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

  
    Graph mst = Algorithms::Prim(g);
    int edgeCount = 0;
    for (int u = 0; u < mst.getVertexCount(); ++u) {
        EdgeNode* edge = mst.getAdjList()[u].head;
        while (edge != nullptr) {
            if (u < edge->destination) 
                edgeCount++;
            edge = edge->next;
        }
    }

    CHECK(edgeCount == 4);
    int totalWeight = 0;
    for (int u = 0; u < mst.getVertexCount(); ++u) {
        EdgeNode* edge = mst.getAdjList()[u].head;
        while (edge != nullptr) {
            if (u < edge->destination)
                totalWeight += edge->weight;
            edge = edge->next;
        }
    }

    CHECK(totalWeight == 16);
}

TEST_CASE("Prim on single-node graph") {
    Graph g(1);
    Graph mst = Algorithms::Prim(g);
    int edgeCount = 0;
    for (int u = 0; u < mst.getVertexCount(); ++u) {
        EdgeNode* edge = mst.getAdjList()[u].head;
        while (edge != nullptr) {
            if (u < edge->destination)
                edgeCount++;
            edge = edge->next;
        }
    }
    CHECK(edgeCount == 0);
}

TEST_CASE("Prim on disconnected graph") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 2);
    Graph mst = Algorithms::Prim(g);
    int edgeCount = 0;
    for (int u = 0; u < 4; ++u) {
        EdgeNode* edge = mst.getAdjList()[u].head;
        while (edge != nullptr) {
            if (u < edge->destination)
                edgeCount++;
            edge = edge->next;
        }
    }
    CHECK(edgeCount < 3);  
}

// ----------------Test - Kruskal--------------
TEST_CASE("Kruskal on simple connected graph") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 6);
    g.addEdge(2, 3, 3);

    Graph mst = Algorithms::Kruskal(g);
    int edgeCount = 0, totalWeight = 0;
    for (int u = 0; u < mst.getVertexCount(); ++u) {
        EdgeNode* e = mst.getAdjList()[u].head;
        while (e) {
            if (u < e->destination)
                edgeCount++, totalWeight += e->weight;
            e = e->next;
        }
    }

    CHECK(edgeCount == 3);       
    CHECK(totalWeight == 6);     
}

TEST_CASE("Kruskal with equal weights") {
    Graph g(3);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(0, 2, 1);

    Graph mst = Algorithms::Kruskal(g);

    int edgeCount = 0, totalWeight = 0;
    for (int u = 0; u < 3; ++u) {
        EdgeNode* e = mst.getAdjList()[u].head;
        while (e) {
            if (u < e->destination)
                edgeCount++, totalWeight += e->weight;
            e = e->next;
        }
    }

    CHECK(edgeCount == 2);
    CHECK(totalWeight == 2);
}

TEST_CASE("Kruskal on disconnected graph") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 2);
    Graph mst = Algorithms::Kruskal(g);
    int edgeCount = 0, totalWeight = 0;
    for (int u = 0; u < 4; ++u) {
        EdgeNode* e = mst.getAdjList()[u].head;
        while (e) {
            if (u < e->destination)
                edgeCount++, totalWeight += e->weight;
            e = e->next;
        }
    }
    CHECK(edgeCount == 2);        
    CHECK(totalWeight == 3);     
}
