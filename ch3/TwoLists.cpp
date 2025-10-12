#include "Ch3.h"
#include <print>

void ch3::printLots(std::list<int> l, std::list<int> p)
{
  for (auto it = p.begin(); it != p.end(); ++it) {
    int n = *it;
    auto lit = l.begin();
    for (int i = 0; i != n; ++i) {
      ++lit;
    }
    std::print("{} ", *lit);
  }
  std::println("");
}