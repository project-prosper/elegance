#include "module2.h"
#define NIL -1


//------------------------------------

Edge::Edge(int u, int v)
{
	this->u = u;
	this->v = v;
}






std::vector<unsigned> findArtPts (Graph g) {
    
    std::vector<unsigned> artPts;
    
    if(g.directed) {
        throw std::runtime_error("Function to find APs only implemented for undirected graphs.\n");
    }
    
	
	std::set<unsigned> notVisited;
	
	for (unsigned i = 1; i <= g.numVert; i++) {
	    notVisited.insert(i);
	}
	
	
	while(!notVisited.empty()) {
	    
	    Dfs dfsObj {g, *notVisited.begin()};
	    
	    for(unsigned i = 1; i <= dfsObj.numVert; ++i) {
	        if(dfsObj.explored[i]) {
	            
	            bool ap = false;
	            
	            for(unsigned j = 1; j <= dfsObj.numVert; ++j) {
	                if(dfsObj.dfsTree[i][j] && dfsObj.dfsNoGivInd[i] < dfsObj.dfsNoGivInd[j]) { //j is a child
	                    if(dfsObj.lowPoint[j] >= dfsObj.dfsNoGivInd[i]) //there's one branch for which lowPoint >= dfs(i)
	                        ap = true;
	                }
	            }
	            
	            if(ap) {
	                artPts.push_back(i);
	            }
	        }
	    } 
	    
	    for (unsigned i = 1; i <= g.numVert; i++) {
	        
	        if(dfsObj.explored[i]) { //if i is discovered
	            notVisited.erase(i); //remove i
	        }
	    }
	}
    
    
    return artPts;
}











std::vector<std::pair <unsigned, unsigned> > findBridges (Graph g) {
    
      if(g.directed) {
        throw std::runtime_error("findBridges been implemented for undirected graphs only.\n");
    }
	
	std::vector<std::pair<unsigned, unsigned> >bridge;
	std::set<unsigned> notVisited;
	
	for (int i = 1; i <= g.numVert; i++) {
	    notVisited.insert(i);
	}
	
	
	while(!notVisited.empty()) {
	    
	    Dfs obj {g, *notVisited.begin()};
	    
	    for(unsigned i = 1; i <= g.numVert; i++) {
	        
	        for(unsigned j = 1; j <= g.numVert; j++) {
	            
	            if(obj.dfsTree[i][j]) {
	                
	                if(obj.dfsNoGivInd[i] > obj.dfsNoGivInd[j]) {
	                    
	                    if(obj.lowPoint[i] == obj.dfsNoGivInd[i]) {
	                        
	                        bridge.push_back(std::make_pair(i,j));
	                        
	                    }
	                }
	            }
	            
	        }
	    }
	    for(unsigned i = 1; i <= g.numVert; i++) {
	        if(obj.explored[i])
	        notVisited.erase(i);
	    }
	    
	    
	   
	}
	return bridge;
}




void comp(int v,bool visited[],Graph g) {
    visited[v]=true;
    std::cout<<v<<" ";
    
    for(int i=1;i<=g.numVert;i++)
    if(!visited[i]&&g.adjMat[v][i]==1)
    comp(i,visited,g);
}


void strong_contd_comp(Graph g) {
    std::stack<int> stack1;
    std::stack<int> temp;	//for display purposes.
    bool visited[g.numVert];
    
    for(unsigned i=1;i<=g.numVert;i++)
	visited[i]=false;
	    
    for(unsigned i=1;i<=g.numVert;i++)
    {
        if(visited[i]==false)
            fillstack(i,visited,&stack1,g);
    }
    
    
    Graph rg=rev(g);
    rg.disp();
	
	/*for(int i=1;i<=rg.numVert;i++)
	{
		for(int j=1;j<=rg.numVert;j++)
    	std::cout<<rg.adjMat[i][j]<<" ";
    	std::cout<<std::endl;
	}
    */
    
    for(int i=1;i<=g.numVert;i++)
        visited[i]=false;
	while(!stack1.empty()) {
        int v=stack1.top();
        stack1.pop();
    	if(visited[v]==false) {
        	comp(v,visited,rg);
        	std::cout<<std::endl;
           }
    }
}
void fillstack(int v, bool visited[],std::stack<int> *stack1,Graph g) {
    visited[v]=true;
    
    for(unsigned i=1;i<=g.numVert;i++) {
    	if(g.adjMat[v][i]==1 &&!visited[i])
        fillstack(i,visited,stack1,g);
    }
  
    stack1 -> push(v);
}

Graph rev(Graph g) {
    Graph temp(g.numVert,true);
    for(int i=1;i<=g.numVert;i++) {
        for(int j=1;j<=g.numVert;j++)
        	if(g.adjMat[i][j]==1)
        		temp.adjMat[j][i]=1;
    }
    //std::cout<<"Transpose Graph:"<<std::endl;
 /*   	for(int i=1;i<=temp.numVert;i++)
	{
		for(int j=1;j<=temp.numVert;j++)
    	std::cout<<temp.adjMat[i][j]<<" ";
    	std::cout<<std::endl;
	}
*/
    return temp;
}


//-------------------biconnected------------------------


void BCCUtil(Graph g,int u, int disc[], int low[], std::list<Edge> *st,int parent[])
{

	static int time = 0;
	int v;

	disc[u] = low[u] = ++time;
	int children = 0;



	for (int i = 1;i<=g.numVert;i++)
	{	

	
			
		if(g.adjMat[u][i]==1)
		 {
		 v = i; 
	
		
	
		if (disc[v] == -1)
		{
			children++;
			parent[v] = u;
	
			st->push_back(Edge(u,v));
			BCCUtil(g,v, disc, low, st, parent);

			low[u] = std::min(low[u], low[v]);

	
			if( (disc[u] == 1 && children > 1) ||
				(disc[u] > 1 && low[v] >= disc[u]) )
			{
				while(st->back().u != u || st->back().v != v)
				{
					std::cout << st->back().u << "--" << st->back().v << " ";
					st->pop_back();
				}
				std::cout << st->back().u << "--" << st->back().v;
				st->pop_back();
				std::cout << std::endl;

			}
		}

		else if(v != parent[u] && disc[v] < low[u])
		{
			low[u] = std::min(low[u], disc[v]);
			st->push_back(Edge(u,v));
		}
		}
}

}



void BCC(Graph g)
{
	int *disc = new int[g.numVert];
	int *low = new int[g.numVert];
	int *parent = new int[g.numVert];
	std::list<Edge> *st = new std::list<Edge>[18];


	for (int i = 1; i <= g.numVert; i++)
	{
		disc[i] = NIL;
		low[i] = NIL;
		parent[i] = NIL;
	}

	for (int i = 1; i <= g.numVert; i++)
	{
		if (disc[i] == NIL)
			BCCUtil(g,i, disc, low, st, parent);
		
		int j = 0;

		while(st->size() > 0)
		{
			j = 1;
			std::cout << st->back().u << "--" << st->back().v << " ";
			st->pop_back();
		}
		if(j == 1)
		{
			std::cout << std::endl;

		}
	}
}
//--------------------------------------------------------------
/*int main(void) {
    
    Graph g {5, false};
   g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(2, 1);
    g.addEdge(4, 1);
    //g.addEdge(4, 5);
   // g.addEdge(1, 2);
    //g.addEdge(2, 3);
   // g.addEdge(3, 4);
   // g.addEdge(1, 4);
   // g.addEdge(4, 5);
    std::cout<<"main";
    g.disp();
    std::cout<<std::endl;
    strong_contd_comp(g);
    
    std::cout << "ArtPts:\n";
    disp(findArtPts(g));
    std::cout << "Bridges:\n";
    disp(findBridges(g));
    
 
    
    Graph g(12,false);
	g.addEdge(1,2);g.addEdge(2,1);
	g.addEdge(2,3);g.addEdge(3,2);
	g.addEdge(2,4);g.addEdge(4,2);
	g.addEdge(3,4);g.addEdge(4,3);
	g.addEdge(3,5);g.addEdge(5,3);
	g.addEdge(4,5);g.addEdge(5,4);
	g.addEdge(2,6);g.addEdge(6,2);
	g.addEdge(1,7);g.addEdge(7,1);
	g.addEdge(6,7);g.addEdge(7,6);
	g.addEdge(6,8);g.addEdge(8,6);
	g.addEdge(6,9);g.addEdge(9,6);
	g.addEdge(8,9);g.addEdge(9,8);
	g.addEdge(9,10);g.addEdge(10,9);
	g.addEdge(11,12);g.addEdge(12,11);
	g.disp();
	std::cout<<"done--GRAPH CREATED"<<endl;
	BCC(g);
	
	std::cout << "Above are  biconnected components in graph";
	

	
    return 0;
}*/