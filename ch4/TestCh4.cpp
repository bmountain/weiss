#include "Ch4.h"
#include <gtest/gtest.h>
#include <set>
#include <vector>

TEST(TestBinarySearchTree, Insert)
{
  BinarySearchTree<int> tree;
  for (int i = 0; i != 10; ++i) {
    tree.insert(i);
  }
  EXPECT_EQ(tree.findMin(), 0);
  EXPECT_EQ(tree.findMax(), 9);
}

TEST(TestBinarySearchTree, Remove)
{
  BinarySearchTree<int> tree;
  for (int i = 0; i != 10; ++i) {
    tree.insert(i);
  }
  for (int i = 8; i != 11; ++i) {
    tree.remove(i);
  }
  EXPECT_EQ(tree.findMax(), 7);

  for (int i = 0; i != 3; ++i) {
    tree.remove(i);
  }
  EXPECT_EQ(tree.findMin(), 3);
}

TEST(TestBinarySearchTree, Iterator)
{
  BinarySearchTree<int> tree;
  std::set<int> numSet;
  std::vector<int> numbers = {5, 1, 3, -1};
  for (const auto n : numbers) {
    tree.insert(n);
    numSet.insert(n);
  }
  auto itTree = tree.begin();
  auto itSet = numSet.begin();
  while (itTree != tree.end()) {
    EXPECT_EQ(*itTree, *itSet);
    ++itTree;
    ++itSet;
  }
}