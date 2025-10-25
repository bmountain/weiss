#include "Hash.h"
#include "HashTable.h"
#include "PrimeNumber.h"
#include "SeparatedChaining.h"
#include <gtest/gtest.h>
#include <print>

TEST(TestPrime, Basic)
{
  EXPECT_EQ(nextPrime(100), 101);
  EXPECT_EQ(nextPrime(1000), 1009);
}

TEST(TestSeparatedChainning, Basic)
{
  SeparatedChaining<std::string> ht{5, hash<std::string>{}};
  EXPECT_TRUE(ht.insert("Hello"));
  EXPECT_TRUE(ht.contains("Hello"));
  EXPECT_FALSE(ht.insert("Hello"));
  EXPECT_TRUE(ht.remove("Hello"));
  EXPECT_FALSE(ht.contains("Hello"));
  for (size_t i = 0; i != 20; ++i) {
    EXPECT_TRUE(ht.insert(std::to_string(i)));
  }
}

TEST(TestQuadraticProbing, Basic)
{
  HashTable<std::string> ht{5, hash<std::string>{}};
  EXPECT_TRUE(ht.insert("Hello"));
  EXPECT_TRUE(ht.contains("Hello"));
  EXPECT_FALSE(ht.insert("Hello"));
  EXPECT_TRUE(ht.remove("Hello"));
  EXPECT_FALSE(ht.contains("Hello"));
  for (size_t i = 0; i != 20; ++i) {
    EXPECT_TRUE(ht.insert(std::to_string(i)));
  }
}
