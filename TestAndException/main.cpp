//ronamsalem4@gmail.com
#include "AdjacencyList/Graph.hpp"
#include "Algorithms/Algorithms.hpp"
#include "TestAndException/GraphError.hpp"
#include "MyDataStructures/Queue.hpp"

using namespace graph;

int main() {
    
    Graph gBFS(13);
    Graph gDfs(6);
    Graph gDij(4);
    Graph gPrim(5);
    Graph gKruskal(9);

   // ------------BFS-EXAMPLE ----------
   gBFS.addEdge(0, 1);  
   gBFS.addEdge(0, 4);  
   gBFS.addEdge(0, 3);  
   gBFS.addEdge(0, 2);  
   gBFS.addEdge(1, 5);  
   gBFS.addEdge(1, 7);  
   gBFS.addEdge(2, 6);  
   gBFS.addEdge(3, 6);  
   gBFS.addEdge(4, 10);   
   gBFS.addEdge(5, 6); 
   gBFS.addEdge(5, 8); 
   gBFS.addEdge(7, 9);  
   gBFS.addEdge(7, 10);
   gBFS.addEdge(8, 11); 
   gBFS.addEdge(8, 12); 
   gBFS.addEdge(9, 12); 
   gBFS.addEdge(10, 12); 

 Graph bfsTree = Algorithms::BFS(gBFS, 0);
std::cout << "\nBFS Tree:\n";
    bfsTree.printGraph();


// ------------DFS-EXAMPLE ----------

gDfs.addEdge(0, 1);
gDfs.addEdge(0, 2);
gDfs.addEdge(2, 1);
gDfs.addEdge(1, 3);
gDfs.addEdge(4,3);
gDfs.addEdge(4, 5);
Graph dfsTree = Algorithms::DFS(gDfs, 0);
  std::cout << "\n DFS Tree:\n";
      dfsTree.printGraph();

// -----------Dijkstra-EXAMPLE ----------

gDij.addEdge(0, 1, 10); // A - B (10)
gDij.addEdge(0, 2, 6);  // A - C (6)
gDij.addEdge(0, 3, 5);  // A - D (5)
gDij.addEdge(1, 3, 15); // B - D (15)
gDij.addEdge(2, 3, 4);
Graph dijTree = Algorithms::Dijkstra(gDij,0);
std::cout << "\nDijkstra  Tree:\n";
dijTree.printGraph();


// -----------prim-EXAMPLE ----------
   gPrim.addEdge(0,1,18);
   gPrim.addEdge(0,2,24);
   gPrim.addEdge(0,3,25);
   gPrim.addEdge(0,4,19);
   gPrim.addEdge(4,2,29);
   
    
    Graph res = Algorithms::Prim(gPrim);
    std::cout << "\nPrim  Tree:\n";
    res.printGraph();


// -----------Kruskal-EXAMPLE ----------
gKruskal.addEdge(0,3,1);
gKruskal.addEdge(0,1,9);
gKruskal.addEdge(1,2,3);
gKruskal.addEdge(2,3,5);
gKruskal.addEdge(1,4,4);
gKruskal.addEdge(4,2,1);
gKruskal.addEdge(1,5,3);
gKruskal.addEdge(4,8,6);
gKruskal.addEdge(8,7,1);
gKruskal.addEdge(7,6,2);
gKruskal.addEdge(5,7,2);
gKruskal.addEdge(5,6,5);
gKruskal.addEdge(2,5,12);
gKruskal.addEdge(3,6,8);

    Graph res1 = Algorithms::Kruskal(gKruskal);
    std::cout << "\nKruskal Tree:\n";
    res1.printGraph();
    
        return 0;



}
