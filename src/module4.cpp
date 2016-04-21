#include "module4.h"


unsigned topo(Graph g) {
    
    if(!g.numVert) 
    	throw std::runtime_error("topological ordering works only for directed graphs\n");
    
    Graph f {g};
    
    unsigned levelNo = 0;
    
    while(f.adjMat[0][0] != 0) {
    
        ++levelNo;
        
        //collect all courses w/ no prereq
        std::queue<unsigned> q;
        for(unsigned i = 1; i <= f.numVert; i++) {
    
            //check for no prereq
            if(f.adjMat[0][i] == 0) {
                q.push(i);
            }
        }
        
        if(q.empty()) {
            throw std::runtime_error("Error in Levels: Cycle in digraph!\n");
        }
            
        { // tightly scoping i
            unsigned i;
            while(!q.empty()) {
                i = q.front();
                q.pop();
                
                for(unsigned j = 1 ; j <= f.numVert ; j++) {
                    
                    if(f.adjMat[i][j]) f.removeEdge(i,j);
                }
            }
        }
    }
    
    return levelNo+1;
}

bool testRamsayF(Graph g) {
	if(g.numVert != 6) {
            throw std::runtime_error("Its not 6 vertices graph!\n");
        }
        std::set<unsigned> notVisited;
	
	for (int i = 1; i <= g.numVert; i++) {
	    notVisited.insert(i);
	}
	bool mfriend = false;
	int comp=0;
	while(!notVisited.empty()) {
	    
	    Bfs bfsObj {g, *notVisited.begin()};
	    
	    /*if(bfsObj.cycle)*/ {
	    	for(unsigned i = 1; i <= g.numVert; i++) {
	    		
	    		for(unsigned j = 1; j <= g.numVert; j++) {
	    			
	    			bool found = false;
	    		
	    					
	    				if(bfsObj.discovered[i] == 1 && bfsObj.discovered[j] == 1) {
	    						if(g.adjMat[i][j] == 1 && bfsObj.bfsTree[i][j] == 0)  {
	    							found = true;
								}
							}
						
					
					unsigned check = 0;
					if(found == true) {
						
						for(unsigned m = 1; m <= g.numVert; m++) {
							check = check + g.adjMat[i][m]*g.adjMat[j][m];
						}
						if(check != 0) {
							mfriend = true;
						}
					}
				}
			}
		}
	    //comp++;
	    for (int i = 1; i <= g.numVert; i++) {
	        
	        if(bfsObj.discovered[i]) { //if i is discovered
	            notVisited.erase(i); //remove i
	        }
	    }
	}

	return mfriend;
}

bool testRamsayE(Graph g) {
	if(g.numVert != 6) {
            throw std::runtime_error("Its not 6-vertex graph!\n");
        }
        std::set<unsigned> notVisited;
	Graph f(g);
	for (int i = 1; i <= f.numVert; i++) {
	    notVisited.insert(i);
	}
	bool menemy = false;
	
	for(unsigned k = 1; k <= f.numVert; k++) {
	    				
	    				for(unsigned l = 1; l <= f.numVert, l != k; l++) {
	    					
	    					if(f.adjMat[k][l]) {
	    						//std::cout<<"removed "<<k<<" "<<l<<std::endl;
	    					 	f.removeEdge(k,l);
	    					 
							}
							else {
								//std::cout<<"adding "<<k<<" "<<l<<std::endl;
								f.addEdge(k,l);
								
							}
						}
					}
	
	while(!notVisited.empty()) {
	    
	    Bfs bfsObj {f, *notVisited.begin()};
	    
	    if(bfsObj.cycle) {
	    	for(unsigned i = 1; i <= f.numVert; i++) {
	    		
	    		for(unsigned j = 1; j <= f.numVert; j++) {
	    			
	    			bool found = false;
	    		
	    					if(bfsObj.discovered[i] == 1 && bfsObj.discovered[j] == 1) {
	    						if(f.adjMat[i][j] == 1 &&bfsObj.bfsTree[i][j] == 0) {
	    							found = true;
								}
							}
						
					
					unsigned check = 0;
					if(found == true) {
						
						for(unsigned m = 1; m <= f.numVert; m++) {
							check = check + f.adjMat[i][m]*f.adjMat[j][m];
						}
						if(check != 0) {
							menemy = true;
						}
					}
				}
			}
		}
	
	    for (int i = 1; i <= g.numVert; i++) {
	        
	        if(bfsObj.discovered[i]) { //if i is discovered
	            notVisited.erase(i); //remove i
	        }
	    }
	}

	return menemy;
}

/*int main(void) {
    
    Graph f {5, true};
    f.addEdge(1, 2);
    f.addEdge(1, 3);
    f.addEdge(3, 4);
    f.addEdge(4, 5);
    //f.addEdge(2, 3);
    //f.addEdge(4, 5);
    f.disp();
    std::cout<<"no of levels   "<< levels(f) << std::endl;
    return 0;
}*/