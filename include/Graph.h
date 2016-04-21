//Graph header. 

#ifndef _Graph_h
#define _Graph_h

#include <vector>
#include <iostream>
#include <stdexcept>
#include <queue> 

class Graph {
public:
    
    std::vector<std::vector<unsigned> > adjMat;
    size_t numVert;
    bool directed;
    
    Graph(unsigned numV, bool dir = true);
    bool addEdge(unsigned from, unsigned to); //indices
    bool removeEdge(unsigned from, unsigned to);
    
    void disp();
};

#endif