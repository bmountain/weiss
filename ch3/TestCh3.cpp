#include "Ch3.h"
#include "List.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <list>
#include <string>

using namespace ch3;

TEST(TestTwoLists, Basic)
{
  std::list<int> l = {1, 2, 3, 4, 5};
  std::list<int> p = {0, 3, 4};
  std::string expected{"1 4 5 \n"};
  testing::internal::CaptureStdout();
  printLots(l, p);
  std::string actual = testing::internal::GetCapturedStdout();
  EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(TestFind, Found)
{
  std::list<int> li = {0, 1, 4, 6, 8};

  auto actual = ch3::find(li.begin(), li.end(), 4);
  auto expected = std::find(li.begin(), li.end(), 4);
  EXPECT_EQ(*actual, *expected);
  EXPECT_EQ(expected, actual);
}

TEST(TestFind, NotFound)
{
  std::list<int> li = {0, 1, 4, 6, 8};

  auto actual = ch3::find(li.begin(), li.end(), 10);
  auto expected = std::find(li.begin(), li.end(), 10);
  EXPECT_EQ(expected, actual);
}

TEST(TestIntersection, Basic)
{
  std::list<int> left = {0, 2, 5, 9};
  std::list<int> right = {1, 2, 3, 9};
  std::list<int> expected = {2, 9};
  auto actual = getIntersection(left, right);
  EXPECT_EQ(expected, actual);
}

TEST(TestUnion, Basic)
{
  std::list<int> left = {0, 2, 5, 9};
  std::list<int> right = {1, 2, 3, 9};
  std::list<int> expected = {0, 1, 2, 3, 5, 9};
  auto actual = getUnion(left, right);
  EXPECT_EQ(expected, actual);
}

TEST(TestJosephas, Basic)
{
  EXPECT_EQ(ch3::josephas(0, 5), 5);
  EXPECT_EQ(ch3::josephas(1, 5), 3);
}

TEST(TestList, PushBack)
{
  ch3::list<int> li;
  li.push_back(1);
  EXPECT_EQ(*(li.begin()), 1);
}

TEST(TestList, Size)
{
  ch3::list<int> li;
  li.push_back(1);
  li.push_back(2);
  li.push_back(3);
  EXPECT_EQ(li.size(), 3);
}

TEST(TestList, Print)
{
  ch3::list<int> li;
  li.push_back(1);
  li.push_back(2);
  li.push_back(3);

  testing::internal::CaptureStdout();
  li.print();
  auto actual = testing::internal::GetCapturedStdout();
  EXPECT_STREQ(actual.c_str(), "1 2 3 \n");
}

TEST(TestList, Contains)
{
  ch3::list<int> li;
  li.push_back(1);
  li.push_back(2);
  li.push_back(3);

  EXPECT_TRUE(li.contains(1));
  EXPECT_FALSE(li.contains(0));
}

TEST(TestList, Insert)
{
  ch3::list<int> li;
  li.push_back(1);
  li.push_back(2);
  li.push_back(3);

  EXPECT_TRUE(li.insert(4));
  EXPECT_EQ(li.size(), 4);

  EXPECT_FALSE(li.insert(1));
  EXPECT_EQ(li.size(), 4);
}

TEST(TestList, Remove)
{
  ch3::list<int> li;
  li.push_back(1);
  li.push_back(2);
  li.push_back(3);

  li.remove(2);
  EXPECT_EQ(li.size(), 2);
  li.remove(4);
  EXPECT_EQ(li.size(), 2);
}

TEST(TestList2, Minus)
{
  List<int> li;
  li.push_back(1);
  li.push_back(2);
  li.push_back(3);
  auto it = li.end();
  it = it - 2;
  EXPECT_EQ(*it, 2);
}

TEST(TestList2, Plus)
{
  List<int> li;
  li.push_back(1);
  li.push_back(2);
  li.push_back(3);
  auto it = li.begin();
  it = it + 2;
  EXPECT_EQ(*it, 3);
}

TEST(TestList2, Splice)
{
  List<int> li;
  li.push_back(1);
  li.push_back(2);
  li.push_back(3);
  auto it = li.begin() + 1;

  List<int> li0;
  li0.push_back(4);
  li0.push_back(5);
  li.splice(it, li0);
  it = li.begin();
  EXPECT_EQ(*++it, 4);
  EXPECT_EQ(*++it, 5);
  EXPECT_EQ(li0.size(), 0);
}

TEST(TestList2, ReverseIterator)
{
  List<int> li;
  li.push_back(1);
  li.push_back(2);
  li.push_back(3);
  testing::internal::CaptureStdout();
  for (auto it = li.rbegin(); it != li.rend(); ++it) {
    std::cout << *it << std::endl;
  }
  std::string actual = testing::internal::GetCapturedStdout();
  EXPECT_STREQ(actual.c_str(), "3\n2\n1\n");

  const auto li0 = li;
  testing::internal::CaptureStdout();
  for (auto it = li.rbegin(); it != li.rend(); ++it) {
    std::cout << *it << std::endl;
  }
  actual = testing::internal::GetCapturedStdout();
  EXPECT_STREQ(actual.c_str(), "3\n2\n1\n");
}