#include "collection.h"
#include <gtest/gtest.h>

TEST(CollectionTest, Construct)
{
  Collection<int> collection;
  EXPECT_TRUE(collection.isEmpty());
}

TEST(CollectionTest, InsertAndContains)
{
  Collection<int> collection;
  collection.insert(1);
  EXPECT_FALSE(collection.isEmpty());
  EXPECT_TRUE(collection.contains(1));
}

TEST(CollectionTest, MakeEmpty)
{
  Collection<int> collection;
  collection.insert(1);
  collection.makeEmpty();
  EXPECT_TRUE(collection.isEmpty());
}

TEST(CollectionTest, Remove)
{
  Collection<int> collection;
  collection.insert(1);
  collection.insert(2);
  collection.remove(1);
  EXPECT_FALSE(collection.contains(1));
}