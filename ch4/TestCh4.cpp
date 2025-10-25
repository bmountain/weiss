#include "Ch4.h"
#include <gtest/gtest.h>
#include <print>
#include <set>
#include <vector>

TEST(TestStackSearchTree, Insert)
{
  StackSearchTree<int> tree;
  for (int i = 0; i != 10; ++i) {
    tree.insert(i);
  }
  EXPECT_EQ(tree.findMin(), 0);
  EXPECT_EQ(tree.findMax(), 9);
}

TEST(TestStackSearchTree, Remove)
{
  StackSearchTree<int> tree;
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

TEST(TestStackSearchTree, Iterator)
{
  StackSearchTree<int> tree;
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

TEST(TestParentSearchTree, Insert)
{
  ParentSearchTree<int> tree;
  for (int i = 0; i != 10; ++i) {
    tree.insert(i);
  }
  EXPECT_EQ(tree.findMin(), 0);
  EXPECT_EQ(tree.findMax(), 9);
}

TEST(TestParentSearchTree, Remove)
{
  ParentSearchTree<int> tree;
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

TEST(TestParentSearchTree, Iterator)
{
  ParentSearchTree<int> tree;
  std::set<int> numSet;
  std::vector<int> numbers = {5, 8, 1, 6, 3, 9, -1};
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

TEST(TestSet, InsertAndRemove)
{
  Set<int> set;
  for (int i = 0; i != 3; ++i) {
    set.insert(i);
  }
  testing::internal::CaptureStdout();
  for (auto it = set.begin(); it != set.end(); ++it) {
    std::print("{} ", *it);
  }
  auto actual = testing::internal::GetCapturedStdout();
  EXPECT_STREQ(actual.c_str(), "0 1 2 ");

  set.remove(1);
  testing::internal::CaptureStdout();
  for (auto it = set.begin(); it != set.end(); ++it) {
    std::print("{} ", *it);
  }
  actual = testing::internal::GetCapturedStdout();
  EXPECT_STREQ(actual.c_str(), "0 2 ");
}

TEST(TestSet, String)
{
  Set<std::string> set;
  set.insert("a");
  set.insert("b");
  set.insert("c");
  testing::internal::CaptureStdout();
  for (auto it = set.begin(); it != set.end(); ++it) {
    std::print("{} ", *it);
  }
  auto actual = testing::internal::GetCapturedStdout();
  EXPECT_STREQ(actual.c_str(), "a b c ");

  set.remove("b");
  testing::internal::CaptureStdout();
  for (auto it = set.begin(); it != set.end(); ++it) {
    std::print("{} ", *it);
  }
  actual = testing::internal::GetCapturedStdout();
  EXPECT_STREQ(actual.c_str(), "a c ");
}

TEST(TestAvlSearchTree, Insert)
{
  AvlSearchTree<int> tree;
  for (int i = 0; i != 10; ++i) {
    tree.insert(i);
  }
  EXPECT_EQ(tree.findMin(), 0);
  EXPECT_EQ(tree.findMax(), 9);
}

TEST(TestAvlSearchTree, Remove)
{
  AvlSearchTree<int> tree;
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

TEST(TestAvlSearchTree, Iterator)
{
  AvlSearchTree<int> tree;
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
