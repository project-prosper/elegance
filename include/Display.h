#ifndef Display_h
#define Display_h
#include <iostream>
#include <vector>
#include <utility>

void disp(const std::vector<unsigned>& v);

void disp(const std::vector<std::vector<unsigned> >& v);

void disp(const std::vector<std::pair<unsigned, unsigned> >& v);
#endif