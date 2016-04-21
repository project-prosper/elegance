#ifndef module3_h
#define module3_h
#include <iostream>
#include <stdexcept>
#include <algorithm>

#include <set>
#include <list>

#include "Graph.h"
#include "Bfs.h"
#include "Display.h"
#include "module1.h"

std::vector<unsigned> longestPath(Graph g);
void shortWeightedPath(Graph g, unsigned source, unsigned destination);
bool isEvencycle(Graph g);
#endif