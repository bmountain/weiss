#include "Ch3.h"

int ch3::josephas(int m, int n)
{
  std::list<int> li(n);
  std::iota(li.begin(), li.end(), 1);
  std::list<int>::iterator current = li.begin();
  while (li.size() > 1) {
    for (int i = 0; i != m; ++i) {
      if (++current == li.end()) {
        current = li.begin();
      }
    }
    current = li.erase(current);
  }
  return *li.begin();
}