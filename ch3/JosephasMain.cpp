#include "Ch3.h"
#include "measure.h"

int main()
{
  auto func_list = make_function_list(ch3::josephas);
  auto param_list = make_param_list<int, int>({{1, 10000}, {1, 100000}, {1, 1000000}});
  performance_measure(func_list, param_list);
}