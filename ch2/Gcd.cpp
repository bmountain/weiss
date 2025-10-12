#include "Gcd.h"
#include <utility>

int gcd(int a, int b)
{
  while (true) {
    if (a <= b) { // Wlog assume a > b
      std::swap(a, b);
    }

    if (a % b == 0) {
      return b;
    }

    if (a % 2 == 0 && b % 2 == 0) {
      return 2 * gcd(a / 2, b / 2);
    }
    if (a % 2 == 0 && b % 2 == 1) {
      return gcd(a / 2, b);
    }
    if (a % 2 == 1 && b % 2 == 0) {
      return gcd(a, b / 2);
    }
    if (a % 2 == 1 && b % 2 == 1) {
      return gcd((a + b) / 2, (a - b) / 2);
    }
  }
}