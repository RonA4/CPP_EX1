
# C++ Graph Algorithms Project

## Overview

This project implements a fully modular and memory-safe **Graph Algorithms system in C++**, based on the academic courses:
- **Algorithms 1**
- **Systems Programming 1**

The system includes a graph representation, fundamental graph traversal and optimization algorithms, and core data structures – all implemented **without using the STL**.

The project is built with full unit tests using the `doctest` framework and verified for memory safety using `valgrind`.

---

## Implemented Algorithms

- **Breadth-First Search (BFS):**  
  Traverses the graph level-by-level from a source vertex and generates a tree using a parent array.  
  Useful for shortest paths in unweighted graphs.

- **Depth-First Search (DFS):**  
  Explores the graph deeply before backtracking.  
  Useful for cycle detection and topological sorts.

- **Dijkstra’s Algorithm:**  
  Computes shortest paths from a source vertex to all others in a weighted graph.

- **Prim’s Algorithm:**  
  Constructs a Minimum Spanning Tree (MST) by expanding from a starting node using a priority queue.

- **Kruskal’s Algorithm:**  
  Constructs an MST by selecting edges in order of weight while avoiding cycles using the Union-Find structure.

---

## Data Structures

- **Graph (Adjacency List):**  
  Undirected, weighted graph with support for adding and removing edges.

- **Queue:**  
  Standard FIFO queue implemented using an array.

- **Priority Queue:**  
  Basic min-priority queue implemented using an array and linear search.

- **Union-Find (Disjoint Sets):**  
  Used for Kruskal’s algorithm. Implements union by rank and path compression.

---

## Project Structure

```plaintext
EX1_CPP
├── AdjacencyList/           # Graph implementation
│   ├── Graph.cpp / .hpp
├── Algorithms/              # Graph algorithms
│   ├── Algorithms.cpp / .hpp
├── MyDataStructures/        # Core data structures
│   ├── Queue.cpp / .hpp
│   ├── PriorityQueue.cpp / .hpp
│   ├── UnionFind.cpp / .hpp
├── TestAndException/        # Tests and exceptions
│   ├── test.cpp             # Doctest unit tests
│   ├── main.cpp             # Demonstration program
│   ├── doctest.h
│   ├── GraphError.hpp       # Custom exception class
├── Makefile                 # Build system
└── README.md                # Project description (this file)
```

---

## Compilation and Execution

To compile the project, run:

```bash
make
```

### Run the main demo:
```bash
make Main
```

### Run unit tests:
```bash
make test
```

### Check for memory leaks:
```bash
make valgrind
```

### Clean all build artifacts:
```bash
make clean
```



## Author

**Ron Amsalem**  
📧 ronamsalem4@gmail.com
