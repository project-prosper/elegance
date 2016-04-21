#include "Bfs.h"


Bfs::Bfs(Graph g, unsigned root) {
    
    directed = g.directed;
    
    if(!(root <= g.numVert && root >= 1))
        throw std::runtime_error("Error in Bfs: index out of range");
    
    
    numVert = g.numVert;
    
    bfsTree.resize(numVert+1); //Extra row for in degree
    
    
    for(unsigned i = 0; i <= numVert; i++) {
        bfsTree[i].resize(numVert+1); //Extra column for out degree
    }
    
    
    std::queue<unsigned> q;
    discovered.resize(numVert+1);
    levNo.resize(numVert+1); // Level
    
    unsigned currLevel = 0; //Current level
    
    discovered[root] = 1;
    levNo[root] = 0;
    
    q.push(root);
    
    
    cycle = false; //so far no cycle detected
    bipartite = true; //No odd cycle seen so far
    while(!q.empty()) {
        
        unsigned parent = q.front();
        q.pop();
        
        
        for(unsigned j = 1; j <= numVert; ++j) {
            
            if(g.adjMat[parent][j]) { //if j is a neighbour
            
                if(!discovered[j]) { // j is a child
                    addEdge(parent, j);
                    q.push(j);
                    
                    discovered[j] = 1;
                    ++discovered[0]; //Keep track of count
                    levNo[j] = levNo[parent] + 1;
                }
                
                //There is a non-tree edge
                //There is an edge parent->j that is not already a part of the tree
                else if (!bfsTree[parent][j]){
                    cycle = true;
                    if(levNo[parent] == levNo[j]) { //there is at least one cross edge
                        bipartite = false;
                    }
                }
            }
        }
    }
}


bool Bfs::addEdge(unsigned from, unsigned to) {
    
    if(from >= 1 && from <= numVert && to >=1 && to <= numVert && to != from) { //check range
    
        if(bfsTree[from][to]) { //if the edge currently does not exist
            return false;
        }
        
        else {
            
            bfsTree[from][to] = 1;
            ++bfsTree[from][0]; //incr out deg of from
            ++bfsTree[0][to]; //incr in deg of to
            
            ++bfsTree[0][0]; //SUM OF IN & OUT DEG
            
            if(!directed) { //If undirected, also add corresponding edge
                
                bfsTree[to][from] = 1;
                ++bfsTree[to][0];
                ++bfsTree[0][from];
                
                ++bfsTree[0][0]; //SUM OF IN & OUT DEG
            }
            return true;
        }
        
    }
    
    throw std::runtime_error("Error (Bfs addEdge): Index out of range!\n");
}



void Bfs::disp() {
    
    std::cout << "\nBfsTree:" << std::endl;
    
    for (unsigned i = 0; i <= numVert; i++) {
            for (unsigned j = 0; j <= numVert; j++) {
                std::cout << " " << bfsTree[i][j] <<  " ";
            }
            
            std::cout << std::endl;
    }
    
    std::cout << "discovered: \n" << "(";
    
    for (auto x : discovered) {
        std::cout << " " << x << " ";
    }
    
    std::cout << ")" << std::endl;
}



/*int main(void) {
    
    Graph g {5, false};
    g.addEdge(1, 2);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.disp();
    Bfs obj(g, 1);
    obj.disp();
    return 0;
}*/