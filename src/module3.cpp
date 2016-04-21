#include "module3.h"

std::vector<unsigned> longestPath(Graph g) {
     if(!isTree(g)) {
        throw std::runtime_error("Test for longest path only implemented for tree.\n");
    }
    std::vector<unsigned> path;
    
    Bfs obj(g,1);
    unsigned l_path = obj.levNo[1];
    unsigned l_pos ;
    for(unsigned i = 2 ; i <= g.numVert ; i++) {
        if(l_path < obj.levNo[i]) {
            //std::cout<<"1"<<std9::endl;
            l_path = obj.levNo[i];
            l_pos = i;
        }
    }
    //std::cout<<"lops "<<l_pos<<std::endl;
    Bfs obj1(g,l_pos);
    unsigned l_path1 = obj1.levNo[l_pos];
    unsigned l_pos1 ;
    
     for(unsigned i = 1 ; i <= g.numVert ; i++) {
         //std::cout<<"21"<<std::endl;
        if(l_path1 < obj1.levNo[i]) {
            //std::cout<<"2"<<std::endl;
            l_path1 = obj1.levNo[i];
            l_pos1 = i;
        }
    }
   // std::cout<<"lops "<<l_pos1<<std::endl;
    unsigned j = l_pos1;
    path.push_back(l_pos1);
   //std::cout<<l_path1<<" "<<l_pos1<<std::endl;
    while(l_path1 != 0) {
        //std::cout<<"31"<<std::endl;
        for(unsigned i = 1;i <= g.numVert ; i++) {
           // std::cout<<"32"<<std::endl;
            if(obj1.bfsTree[i][j]&&obj1.levNo[i] == obj1.levNo[j]-1) {
               // std::cout<<"3"<<std::endl;
                path.push_back(i);
                l_path1 = obj1.levNo[i];
                //std::cout<<l_path1<<std::endl;
                j=i;
            }
        }
    }
    return path;
}


void shortWeightedPath(Graph g, unsigned source, unsigned destination) {
	if(g.directed) {
		throw std::runtime_error("Test for longest path only implemented for tree.\n");
	}

	Graph graphMain {g.numVert + (unsigned)5*g.numVert, false};
	unsigned weight;
	unsigned used = g.numVert + 1;
	for(unsigned i = 1; i <= g.numVert; i++) {
		for(unsigned j = 1; j <= g.numVert; j++) {
			if(g.adjMat[i][j] && i <= j) { //Consider the upper triangle

				std::cout << "Enter the weight of edge: " << "(" << i << ", " << j << ") ";
				std::cin >> weight; //Get the weight of edge (i ,j)

				//Add dummy vertices and edges
				unsigned curr = i;
				unsigned next = used;
				unsigned end = j;
				for(int k = 0; k < weight-1; k++) {
					graphMain.addEdge(curr, next);
					curr = next;
					next = next + 1;
				}
				//add the final edge
				graphMain.addEdge(curr, end);
				used = next;
			}
		}
	}
	//Call the s_path_fix_vertex function to get the list of spaths from source
	auto levels = s_path_fix_vertex(graphMain, source);
	//Print the shortest path determined by the fn above corresponding to the destination
	std::cout << "Shortest path length:" << levels[destination] << "\n"; 
}

bool isEvencycle(Graph g) {
	bool check = false;
	for(unsigned i = 4; i <= g.numVert; i=i+2) {
		
		for(unsigned j = 0; j <= g.numVert-4 ; j++) {
			
			std::vector<unsigned> tree;
			tree.resize(i);
			for(unsigned l = 0; l < i; l++) {
				tree[l] = j+l+1;
			}
			
			do {
				disp(tree);
				bool ccheck = true;
				unsigned k;
				for( k = 0; k < tree.size()-1; k++) {
					if(!g.adjMat[tree[k]][tree[k+1]]) {
						ccheck = false;
					}
				
				}
					if(!g.adjMat[tree[k]][tree[0]]) {
						ccheck = false; 
					}
				if(ccheck == true) {
					return true;
				}
			}while(std::next_permutation(tree.begin(),tree.end()));
		}
	}
	return check;
	
	
}
/*
int main(void) {
    
    Graph g {4, false};
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 1);
    //g.addEdge(4, 1);
    g.disp();
    Bfs obj(g, 1);
    obj.disp();
    //std::vector<unsigned> path = longestPath( g);
    //std::cout << "longest path" << std::endl;
    //disp(path);
     //isEvenCyclic(g) ? std::cout<<"Exists even Cycle"<<std::endl : std::cout<<"Does not Exist"<<std::endl;
    //std::cout<<"4"<<std::endl;
    std::cout<<"is cycle  "<<isEvencycle(g)<<std::endl;
    return 0;
}*/