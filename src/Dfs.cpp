#include "Dfs.h"


Dfs::Dfs(Graph g, unsigned root)
{

	if(!(root <= g.numVert && root >= 1)) {
        throw std::runtime_error("Error in Dfs: index out of range\n");
	}
    
    numVert = g.numVert;
    directed = g.directed;
    
    dfsTree.resize(numVert+1); 
    
    
    for(unsigned i = 0; i <= numVert; i++) {
     
	    dfsTree[i].resize(numVert+1); 
    }

    std::stack<unsigned> stack;
    explored.resize(numVert+1);
    parentOf.resize(numVert+1);
    
    dfsNoGivInd.resize(numVert+1);
    indGivDfsNo.resize(numVert+1);

    stack.push(root);

    unsigned dfsNo = 0;

    while (!stack.empty()) {

        unsigned current = stack.top();
        stack.pop();

        if(explored[current]) continue; //ALREADY EXPLORED: SKIP

        explored[current] = 1;
        ++explored[0]; //Keep track of count
        
        //DFS NUMBER
        ++dfsNo;
        dfsNoGivInd[current] = dfsNo;
        indGivDfsNo[dfsNo] = current;
        
        //Add Edge
        if(current != root) {
            addEdge(parentOf[current], current);
        }
 
        for (unsigned i = numVert; i >= 1; --i) {
            
            //Check if neighbour
            if (g.adjMat[current][i]) { //could also check for [explored[i] != 1]
                
                stack.push(i);
                parentOf[i] = current;
            }
        }
    }
    
    
    
    //Identifying low-points
    
    lowPoint.resize(numVert+1, numVert+1); //default value is numVert+1 -> indicates not visited by dfs
    
    if(numVert > 0) lowPoint[0] = 0;
    
    for(unsigned dNo = dfsNo; dNo >= 1; --dNo) { //In descending order of dfsNo
        
        unsigned ind = indGivDfsNo[dNo];
        
        unsigned min = dNo;
        
        for(int j = 1; j <= numVert; ++j) {
            
            if(g.adjMat[ind][j] || g.adjMat[j][ind]) { //if j is a neighbor
                
                if(dfsNoGivInd[j] > dfsNoGivInd[ind]) { //j is child / j->ind is a back edge
                    
                    if(lowPoint[j] < min) min = lowPoint[j];
                }
                
                else if(!dfsTree[j][ind]) { //j is not a parent but is an ancestor
                    
                    if(dfsNoGivInd[j] < min) min = dfsNoGivInd[j];
                }
            }
        }
        
        lowPoint[ind] = min;
    }
}



bool Dfs::addEdge(unsigned from, unsigned to) {
    
    if(from >= 1 && from <= numVert && to >=1 && to <= numVert && to != from) { //check range
    
        if(dfsTree[from][to]) { //if the edge currently does not exist
            return false;
        }
        
        else {
            
            dfsTree[from][to] = 1;
            ++dfsTree[from][0]; //incr out deg of from
            ++dfsTree[0][to]; //incr in deg of to
            
            ++dfsTree[0][0]; //SUM OF IN & OUT DEG
            
            
            if(!directed) { //If undirected, also add corresponding edge
                
                dfsTree[to][from] = 1;
                ++dfsTree[to][0];
                ++dfsTree[0][from];
                
                ++dfsTree[0][0]; //SUM OF IN & OUT DEG
            }
            
            return true;
        }
        
    }
    
    throw std::runtime_error("Error (Bfs addEdge): Index out of range!\n");
}


void Dfs::disp() {
    
    std::cout << "\nDfsTree:" << std::endl;
    
    for (unsigned i = 0; i <= numVert; i++) {
            for (unsigned j = 0; j <= numVert; j++) {
                std::cout << " " << dfsTree[i][j] <<  " ";
            }
            
            std::cout << std::endl;
    }
    
    std::cout << "Explored: \n" << "(";
    
    for (auto x : explored) {
        std::cout << " " << x << " ";
    }
    
    std::cout << ")" << std::endl;
}

/*
int main(void) {
    
    Graph g {5, false};
    g.addEdge(1, 2);
    //g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(4, 5);
    g.disp();
    Dfs obj(g, 1);
    
    obj.disp();
    
    std::cout << "dfsNoGivInd:\n";
    disp(obj.dfsNoGivInd);
    std::cout << "indGivDfsNo:\n";
    disp(obj.indGivDfsNo);
    std::cout << "lowPoint:\n";
    disp(obj.lowPoint);
    return 0;
}*/