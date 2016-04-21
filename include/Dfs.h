#ifndef Dfs_h
#define Dfs_h
#include <vector>
#include <iostream>
#include <stdexcept>
#include <stack> 

//Temporary
#include "Graph.h"
#include "Display.h"

class Dfs {
	public:
        //Attribs
        bool directed;
        unsigned numVert;
        
        std::vector<std::vector<unsigned> > dfsTree;
        std::vector<unsigned> explored;
        std::vector<unsigned> parentOf;
        std::vector<unsigned> dfsNoGivInd;
        std::vector<unsigned> indGivDfsNo;
        
        std::vector<unsigned> lowPoint; //L-val for AP's and bridges
        
        //Methods
        Dfs(Graph g, unsigned root);
        bool addEdge(unsigned from, unsigned to);
        void disp();
		
};
#endif