#ifndef Bfs_h
#define Bfs_h
#include <vector>
#include <iostream>
#include <stdexcept>
#include <queue>

//Temporary
#include "Graph.h"

class Bfs {
    public:
        //Attribs
        bool directed;
        bool bipartite;
        bool cycle;
        
        unsigned numVert;
        std::vector<std::vector<unsigned> > bfsTree;
        std::vector<unsigned> discovered;
        std::vector<unsigned> levNo;
        
        
        //Methods
        Bfs(Graph g, unsigned root);
        bool addEdge(unsigned from, unsigned to);
        
        void disp();
};
#endif