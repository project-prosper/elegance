#include <iostream>
#include <vector>
#include <utility>



void disp(const std::vector<unsigned>& v) {
    std::cout << "(";
    for (unsigned x : v) {
        std::cout << " " << x << " ";
    }
    std::cout << ")" << std::endl;
}


void disp(const std::vector<std::vector<unsigned> >& v) {
    std::cout << "\n";
    for (unsigned i = 0; i < v.size(); i++) {
        for (unsigned j = 0; j < v[i].size(); j++) {
            std::cout << " " << v[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void disp(const std::vector<std::pair<unsigned, unsigned> >& v) {
    
    std::cout << "(";
    for (auto x : v) {
        std::cout << " <" << x.first << ", " << x.second << "> ";
    }
    std::cout << ")" << std::endl;
}