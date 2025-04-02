//ronamsalem4@gmail.com
#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP
/**
* @class UnionFind
* A data structure used to efficiently track connected components.
* - Path compression during find
* - Degree union during union
* Commonly used in Kruskal's algorithm to avoid cycles while building the MST.
*/
class UnionFind {
private:
    int* parent;
    int* rank;
    int size;

public:
    UnionFind(int n);
    ~UnionFind();
    int find(int x);
    void unite(int x, int y);
};

#endif
