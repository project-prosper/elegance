#ifndef module1_h
#define module1_h
#include <iostream>
#include <stdexcept>

#include <set>

#include "Graph.h"
#include "Bfs.h"
#include "Display.h"


bool isTree(Graph g);
bool hasCycle(Graph g);
bool isBipartite(Graph g);
std::vector<unsigned> s_path_fix_vertex(Graph , unsigned );
std::vector<std::vector<unsigned> > all_pair_s_path(Graph );
#endif