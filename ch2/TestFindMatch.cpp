#include "FindMatch.h"
#include <gtest/gtest.h>

TEST(FindMatchTest, Basic)
{
  std::vector vec = {0, 1, 2};
  EXPECT_FALSE(find_match(vec));

  vec = {1, 3, 4};
  EXPECT_TRUE(find_match(vec));

  vec = {0, 1, 3};
  EXPECT_TRUE(find_match(vec));

  vec = {0, 2, 4};
  EXPECT_TRUE(find_match(vec));
}