#include "RandomPermutation.h"
#include <gtest/gtest.h>

TEST(FUNC0, UNIQUENESS)
{
  size_t size = 10;
  std::vector<int> vec = func0(size);
  EXPECT_TRUE(vec.size() == size);
  EXPECT_TRUE(std::unique(vec.begin(), vec.end()) == vec.end());
}
