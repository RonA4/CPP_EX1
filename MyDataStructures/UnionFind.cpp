//ronamsalem4@gmail.com
#include "UnionFind.hpp"
/**
 * This file provides the implementation of the UnionFind data structure,
 * Key features:
 *  Path Compression in `find()` to flatten the tree structure
 *  Union by Rank in `unite()` to keep the trees balanced
 * This structure is especially effective in graph algorithms like Kruskal's MST,
 * where we need to detect and prevent cycles.
 */
UnionFind::UnionFind(int n) {
    size = n;
    parent = new int[n];
    rank = new int[n];
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank[i] = 0;   
    }
}

UnionFind::~UnionFind() {
    delete[] parent;
    delete[] rank;
}

int UnionFind::find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // Path Compression
    }
    return parent[x];
}

void UnionFind::unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) return; 

    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
} 
