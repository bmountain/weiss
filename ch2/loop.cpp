#include "measure.h"
#include <chrono>

void func0(int n)
{
  int sum = 0;
  for (int i = 0; i != n; ++i) {
    ++sum;
  }
}

void func1(int n)
{
  int sum = 0;
  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != n; ++j) {
      ++sum;
    }
  }
}

void func2(int n)
{
  int sum = 0;
  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != n * n; ++j) {
      ++sum;
    }
  }
}

void func3(int n)
{
  int sum = 0;
  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != i; ++j) {
      ++sum;
    }
  }
}

void func4(int n)
{
  int sum = 0;
  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != n; ++j) {
      for (int k = 0; k != j; ++k) {
        ++sum;
      }
    }
  }
}

void func5(int n)
{
  int sum = 0;
  for (int i = 1; i != n; ++i) {
    for (int j = 1; j != i; ++j) {
      if (j % i == 0) {
        for (int k = 0; k != j; ++k) {
          ++sum;
        }
      }
    }
  }
}

int main()
{
  auto func_list = make_function_list(func0, func1, func2, func3, func4, func5);
  auto param_list = make_param_list<int>({{10}, {100}, {1000}});
  performance_measure<std::chrono::nanoseconds>(func_list, param_list);
}
