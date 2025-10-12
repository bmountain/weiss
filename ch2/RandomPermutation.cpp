#include "RandomPermutation.h"
#include "measure.h"
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

// discrete uniform distribution
class UniformDist
{
  std::mt19937 engine{};

public:
  UniformDist(uint_fast32_t seed = 0)
  : engine{seed}
  {
  }

  int operator()(int min, int max)
  {
    std::uniform_int_distribution<> dist{min, max};
    return dist(engine);
  }
};

// get original data
std::vector<int> getData(int n)
{
  std::vector<int> vec(n);
  std::iota(vec.begin(), vec.end(), 1);
  return vec;
}

std::vector<int> func0(int n)
{
  UniformDist random{};

  std::vector<int> org = getData(n);
  std::vector<int> ret;
  while (ret.size() != org.size()) {
    int value = org[random(0, org.size() - 1)];
    if (std::find(ret.begin(), ret.end(), value) == ret.end()) {
      ret.push_back(value);
    }
  }
  return ret;
}

std::vector<int> func1(int n)
{
  UniformDist random{};

  std::vector<int> org = getData(n);
  std::vector<int> ret;
  std::vector<bool> used(org.size(), false);
  while (ret.size() != org.size()) {
    int idx = random(0, org.size() - 1);
    if (!used[idx]) {
      used[idx] = true;
      ret.push_back(org[idx]);
    }
  }
  return ret;
}

std::vector<int> func2(int n)
{
  UniformDist random{};

  std::vector<int> org = getData(n);
  std::vector<int> ret(org.size());
  for (size_t i = 0; i != org.size(); ++i) {
    ret[i] = org[i];
    int rand = random(0, i);
    std::swap(ret[rand], ret[i]);
  }
  return ret;
}

int main()
{
  auto function_list0 = make_function_list(func0);
  auto param_list0 = make_param_list<int>({{250}, {500}, {1000}, {2000}});
  performance_measure(function_list0, param_list0);

  auto function_list1 = make_function_list(func1);
  auto param_list1 = make_param_list<int>({{25000}, {50000}, {100000}, {200000}, {400000}, {800000}});
  performance_measure(function_list1, param_list1);

  auto function_list2 = make_function_list(func2);
  auto param_list2 = make_param_list<int>({{100000}, {200000}, {400000}, {800000}, {1600000}, {3200000}, {6400000}});
  performance_measure(function_list2, param_list2);
}