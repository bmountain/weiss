#ifndef INTERMEDIATE_VALUE_H
#define INTERMEDIATE_VALUE_H

#include <functional>
#include <limits>

// Allowable error
constexpr double epsilon = std::numeric_limits<double>::epsilon() * 10;

/**
 * @brief Solves func(x) == 0, assuming func(low) < 0 and func(high) > 0.
 */
double solve(std::function<double(double)> func, double low, double high);

#endif /* INTERMEDIATE_VALUE_H */