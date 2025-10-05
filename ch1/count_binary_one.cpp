#include "count_binary_one.h"
#include <cstdlib>

int count_binary_one(int n)
{
  if (n <= 1) {
    return n;
  }
  int back = count_binary_one(n / 2);
  return n % 2 == 0 ? back : back + 1;
}