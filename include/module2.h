#ifndef module2_h
#define module2_h
#include <iostream>
#include <stdexcept>
#include<stack>          //for strongly conntd components
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <list>
#include "Graph.h"
#include "Dfs.h"
#include "Display.h"

class Edge
{
	public:
	int u;
	int v;
	Edge(int u, int v);
};


std::vector<unsigned> findArtPts (Graph );
std::vector<std::pair <unsigned, unsigned> > findBridges (Graph );
void fillstack(int , bool[], std::stack<int>*,Graph);
Graph rev(Graph);
void strong_contd_comp(Graph );
void fillstack(int , bool visited[],std::stack<int> *stack,Graph );
void BCCUtil(Graph g,int u, int disc[], int low[], std::list<Edge> *st,int parent[]);
void BCC(Graph g);

#endif