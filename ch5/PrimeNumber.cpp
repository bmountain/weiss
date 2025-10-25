#include "PrimeNumber.h"
#include <cmath>

size_t nextPrime(size_t x)
{
  while (true) {
    bool found = true;
    for (size_t n = 2; n <= std::sqrt(x); ++n) {
      if (x % n == 0) {
        found = false;
        break;
      }
    }
    if (found) {
      return x;
    } else {
      ++x;
    }
  }
}