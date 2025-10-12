#include "IntermediateValue.h"
#include <cmath>
#include <functional>
#include <gtest/gtest.h>

using Function = std::function<double(double)>;

TEST(TestIntermediateValue, Basic)
{
  Function cubic = [](double x)
  {
    return std::pow(x, 3);
    ;
  };

  EXPECT_TRUE(std::abs(solve(cubic, -1, 1)) < epsilon);
}

TEST(TestIntermediateValue, Quadratic)
{
  Function f = [](double x)
  {
    return x * x - 2 * x;
  };

  EXPECT_TRUE(std::abs(solve(f, 0.5, 3) - 2) < epsilon);
}