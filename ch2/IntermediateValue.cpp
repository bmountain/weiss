#include "IntermediateValue.h"
#include <cmath>
#include <limits>

double solve(std::function<double(double)> func, double low, double high)
{

  while (true) {
    double mid = (low + high) / 2;
    double val = func(mid);
    if (std::abs(val) < epsilon) {
      return mid;
    }
    if (val < 0) {
      low = mid;
    } else {
      high = mid;
    }
  }
}