#include "OrderedCollection.h"
#include <gtest/gtest.h>

TEST(OrderdCollection, Basic)
{
  OrderedCollection<int> c;
  c.insert(1);
  c.insert(2);
  c.insert(3);
  EXPECT_EQ(c.findMax(), 3);
  EXPECT_EQ(c.findMin(), 1);
}

TEST(OrderedCollection, Reference)
{
  OrderedCollection<int> c;
  c.insert(1);
  c.insert(2);
  c.insert(3);

  c.findMax() = 0;
  EXPECT_EQ(c.findMax(), 2);
  c.findMin() = 3;
  EXPECT_EQ(c.findMax(), 3);
}