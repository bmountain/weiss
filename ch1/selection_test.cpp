#include "selection.h"
#include <gtest/gtest.h>

TEST(SelectionTest, PositiveCase)
{
  std::vector<int> vec = {3, 1, 2, 4};
  EXPECT_EQ(selection(vec, 2), 3);
}

TEST(SelectionTest, NegativeCase)
{
  std::vector<float> vec = {-1, -2, -3, -4, -5};
  EXPECT_EQ(selection(vec, 2), -2);
}