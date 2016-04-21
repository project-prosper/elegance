#include <iostream>

#include "module1.h"
#include "module2.h"
#include "module3.h"
#include "module4.h"
#include "Display.h"

using namespace std;

Graph readGraph() {
    int numV, x, y;
    bool directed;
    cout << "------------------ELEGANCE-graph-input-menu---------------------------\n";
    cout << "Enter the number of vertices: ";
    cin >> numV;
    cout << "isDirected ? 1 - YES, 0 - NO";
    cin >> directed;
    Graph g {numV, directed};
    while(true) {
        cout << "Enter space seperated integers (edges). (0 to abort): ";
        cin >> x >> y;
        if(x == 0 || y == 0) 
            break;
        g.addEdge(x, y);
    }
    cout << "------------------------------------------------------\n";
    return g;
}

void handleCases(short int &ch, Graph &g) {
    int vert, vert1;
    switch(ch) {
            case 18:
                    return ;
            case 1: 
                    try {
                        cout << "Enter start-vertex: ";
                        cin >> vert;
                        Bfs obj {g, vert};
                        cout << "Generated BFS tree: \n";
                        obj.disp();
                    }
                    catch(exception &e) {
                        cout << e.what();
                    }
                    break;
            case 2: 
                    try {
                        cout << "Enter start-vertex: ";
                        cin >> vert;
                        Dfs obj {g, vert};
                        cout << "Generated DFS tree: \n";
                        obj.disp();
                    }
                    catch(exception &e) {
                        cout << e.what();
                    }
                    break;
            case 3: 
                    try {
                        bool cycle = hasCycle(g);
                        cout << "Graph hasCycle: " << cycle << "\n";
                    }
                    catch(exception &e) {
                        cout << e.what();
                    } 
                    break;        
            case 4: 
                    try {
                        bool tree = isTree(g);
                        cout << "Graph isTree: " << tree << "\n";
                    }
                    catch(exception &e) {
                        cout << e.what();
                    } 
                    break;
            case 5: 
                    try {
                        bool bipartite = isBipartite(g);
                        cout << "Graph isBipartite: " << bipartite << "\n";
                    }
                    catch(exception &e) {
                        cout << e.what();
                    } 
                    break;
            case 6:  
                    try {
                        cout << "Enter start vertex for s_path_fix_vertex: ";
                        cin >> vert;
                        s_path_fix_vertex(g, vert);
                    }
                    catch(exception &e) {
                        cout << e.what();
                    } 
                    break;
            case 7: 
                   try {
                        cout << "all_pair_s_path: \n";
                        all_pair_s_path(g);
                    }
                    catch(exception &e) {
                        cout << e.what();
                    } 
                    break;
            case 8: 
                   try {
                        cout << "Articulation points: \n";
                        auto artPts = findArtPts(g);
                        disp(artPts);
                    }
                    catch(exception &e) {
                        cout << e.what();
                    } 
                    break;
            case 9:
                    try {
                        cout << "Bridges: \n";
                        auto bridges = findBridges(g);
                        disp(bridges);
                    }
                    catch(exception &e) {
                        cout << e.what();
                    } 
                    break;
            case 10:
                    try {
                        cout << "Strongly connected components: \n";
                        strong_contd_comp(g);
                    }
                    catch(exception &e) {
                        cout << e.what();
                    } 
                    break;
            case 11:
                    try {
                        cout << "Biconnected components: \n";
                        BCC(g);
                    }
                    catch(exception &e) {
                        cout << e.what();
                    } 
                    break;
            case 12:
                    try {
                        cout << "Enter start and end vertices: \n";
                        cin >> vert >> vert1;
                        shortWeightedPath(g, vert, vert1);
                    }
                    catch(exception &e) {
                        cout << e.what();
                    } 
                    break;
            case 13:
                    try {
                        bool evenCycle = isEvencycle(g);
                        cout << "Graph hasEvenTree: " << evenCycle << "\n";
                    }
                    catch(exception &e) {
                        cout << e.what();
                    } 
                    break;
            case 14:
                    try {
                        auto path = longestPath(g);
                        cout << "Longest path in the tree: ";
                        disp(path);
                    }
                    catch(exception &e) {
                        cout << e.what();
                    } 
                    break;
            case 15:
                    try {
                        bool frnd = testRamsayF(g), enemy = testRamsayE(g);
                        cout << "There are 3 mutual friends: " << frnd << endl;
                        cout << "There are 3 mutual enemies: " << enemy << endl;
                    }
                    catch(exception &e) {
                        cout << e.what();
                    }
                    break;
            case 16:
                    try {
                        cout << "Topological ordering/ course prerequistes graph: \n";
                        cout << "#Years = " << topo(g) << "\n";
                    }
                    catch(exception &e) {
                        cout << e.what();
                    }
                    break;
            case 17:
                    g.disp();
                    break;
        }
}

void main_menu() {
    short int ch = 1;
    while(true) {
        Graph g = readGraph();
        //system("clear");
        cout << "------------------------ELEGANCE-main-menu---------------------\n"
             << "Enter choice: \n"
             << "\t-------Module-0----------\n"
             << "1 . BFS \n"
             << "2 . DFS \n"
             << "\t-------Module-1----------\n"
             << "3 . Test Cyclicity\n"
             << "4 . Test Treeness\n"
             << "5 . Test Bipartiteness\n"
             << "6 . Find Shortest Path Fixed Vertex\n"
             << "7 . All pairs spath\n"
             << "\t-------Module-2----------\n"
             << "8 . Articulation points\n"
             << "9 . Bridges\n"
             << "10. Biconnected Components\n"
             << "11. Strongly connected components \n"
             << "\t-------Module-3----------\n"
             << "12. Shortest path - weighted graph\n"
             << "13. Even Cycle testing\n"
             << "14. Longest path in a tree (diameter)\n"
             << "\t-------Module-4----------\n"
             << "15. Ramsey's magic\n"
             << "16. Course prerequistes graph\n"
             << "\t-----------------\n"
             << "17. Display\n"
             << "18. Exit\n";
        handleCases(ch, g);
    }
    
}


int main(void) {
    main_menu();
    return 0;
}