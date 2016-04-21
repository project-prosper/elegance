#include "Graph.h"
#include "Bfs.h"
#include "Display.h"
#include "module1.h"
bool isTree(Graph g) {

    /*
    
        Based on the fact that a graph of n vertices is a tree if:
    
        1) It is connected (bfs covers all nodes).
        2) It has n-1 edges (sum of degrees = 2*n - 2).
    
    */

    if(g.directed) {
        throw std::runtime_error("Test for tree only implemented for undirected graphs.\n");
    }

	unsigned edgeCountX2 = 0; //count edges in graph
	
	bool isConnected = true, flagNovert = true; // flag Novert checks if numEdges = 2*numVerts - 2
	
	Bfs bfsObj {g, 1};
	
	//checking for connectedness
	for(unsigned i = 1; i <= g.numVert; i++) {
	
	    //Check if there is no edge to/from a vertex in bfs tree
		if(bfsObj.bfsTree[0][i] ==  0 && bfsObj.bfsTree[i][0] == 0) {
		    
			isConnected = false;
		}
	}
	
	//Count total num of edges in original graph
	for(unsigned i = 1 ; i <= g.numVert ; i++) {
		edgeCountX2 = edgeCountX2 + g.adjMat[0][i];
	}
	
	//checking edge count=2n-2
	if(edgeCountX2 != ((g.numVert)*2) - 2) 
		flagNovert = false;
	
	
 	return (isConnected && flagNovert);
} 

bool hasCycle(Graph g) {
	
	if(g.directed) {
        throw std::runtime_error("Cyclicity test has been implemented for undirected graphs only.\n");
    }
	
	
	std::set<unsigned> notVisited;
	
	for (int i = 1; i <= g.numVert; i++) {
	    notVisited.insert(i);
	}
	
	
	while(!notVisited.empty()) {
	    
	    Bfs bfsObj {g, *notVisited.begin()};
	    
	    if(bfsObj.cycle) return true; //cycle in that component
	    
	    for (int i = 1; i <= g.numVert; i++) {
	        
	        if(bfsObj.discovered[i]) { //if i is discovered
	            notVisited.erase(i); //remove i
	        }
	    }
	}

    return false;
}

bool isBipartite(Graph g) {
    
    if(g.directed) {
        throw std::runtime_error("Bipartite test has been implemented for undirected graphs only.\n");
    }
	
	
	std::set<unsigned> notVisited;
	
	for (int i = 1; i <= g.numVert; i++) {
	    notVisited.insert(i);
	}
	
	
	while(!notVisited.empty()) {
	    
	    Bfs bfsObj {g, *notVisited.begin()};
	    
	    if(!bfsObj.bipartite) return false; //that component not bipartite => whole raph not bipartite
	    
	    for (int i = 1; i <= g.numVert; i++) {
	        
	        if(bfsObj.discovered[i]) { //if i is discovered
	            notVisited.erase(i); //remove i
	        }
	    }
	}

    return true;
}

std::vector<unsigned> s_path_fix_vertex(Graph g, unsigned vert) {
    auto obj = Bfs(g, vert);
    for(unsigned i = 1; i <= g.numVert; i++) {
            unsigned j;
            if(i != vert) {
            int temp = obj.levNo[i];
            std::cout<<"path "<<i<<" to "<<vert<<std::endl;
            std::cout<<i<<" - ";
            unsigned temp2 = i;
            while(temp >= 0) {
                temp = temp - 1;
                
                for( j = 1; j <= g.numVert; j++) {
                    if(obj.levNo[j] == temp && obj.bfsTree[j][temp2]) {
                        std::cout <<j<<" - ";
                    }  
                }
                temp2 = j;
            }
            std::cout<<std::endl;
        }
        
     
    }
       return obj.levNo;
}



std::vector<std::vector<unsigned> > all_pair_s_path(Graph g) {
	
    std::vector<std::vector<unsigned> > sLen; 
    sLen.resize(g.numVert+1);
    for(unsigned i = 0; i <= g.numVert; i++) {
        sLen[i].resize(g.numVert+1); 
    }
    
        //std::cout << "L: 139" << std::endl;

    
    for(unsigned i = 1; i <= g.numVert ; i++) {
        auto obj = Bfs(g,i);
        for(unsigned j = 1; j <= g.numVert ; j++) {
            sLen[i][j] = obj.levNo[j];
        }
    }
    for(unsigned o = 1; o <= g.numVert; o++) {
        s_path_fix_vertex(g,o);
    }
    
    //std::cout << "L: 149" << std::endl;
    
    return sLen;
}

/*int main(void) {
    
    Graph g {5, false};
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    //g.addEdge(2, 5);
    //g.addEdge(2, 3);
    //g.addEdge(4, 5);
    g.disp();

    s_path_fix_vertex(g, 1);
    //all_pair_s_path(g);
    
    return 0;
}*/

