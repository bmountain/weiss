#include "selection.h"
#include <print>

int main()
{
  std::vector<int> vec = {1, 3, 2};
  std::println("{}", selection(vec, 2).value_or(-1));
}