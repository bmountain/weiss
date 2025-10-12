#include "Ch3.h"
#include "measure.h"
#include "random_number.h"
#include <list>
#include <print>

int main()
{
  auto l0{uniform_random_sequence<std::list>(500, 0, 1000, true, true)};
  auto p0{uniform_random_sequence<std::list>(500, 0, 1000, true, true)};
  auto l1{uniform_random_sequence<std::list>(5000, 0, 10000, true, true)};
  auto p1{uniform_random_sequence<std::list>(5000, 0, 10000, true, true)};
  auto l2{uniform_random_sequence<std::list>(50000, 0, 100000, true, true)};
  auto p2{uniform_random_sequence<std::list>(50000, 0, 100000, true, true)};
  auto data = make_param_list<std::list<int>, std::list<int>>({{l0, p0}, {l1, p1}, {l2, p2}});

  auto func_list = make_function_list(ch3::printLots);
  performance_measure(func_list, data);
}