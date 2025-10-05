#include "count_binary_one.h"
#include <gtest/gtest.h>

TEST(CountTest, BasicTest)
{
  EXPECT_EQ(count_binary_one(0), 0);
  EXPECT_EQ(count_binary_one(1), 1);
  EXPECT_EQ(count_binary_one(7), 3);
  EXPECT_EQ(count_binary_one(8), 1);
  EXPECT_EQ(count_binary_one(1023), 10);
}