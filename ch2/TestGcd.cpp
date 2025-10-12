#include "Gcd.h"
#include <gtest/gtest.h>

TEST(TestGcd, Basic)
{
  EXPECT_EQ(gcd(12, 18), 6);
  EXPECT_EQ(gcd(12, 9), 3);
  EXPECT_EQ(gcd(63, 49), 7);
}