#ifndef RANDOM_NUMBER_H
#define RANDOM_NUMBER_H

#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

template <typename Number>
auto get_uniform_dist(Number min, Number max) ->
    typename std::conditional<std::is_integral_v<Number>, std::uniform_int_distribution<Number>, std::uniform_real_distribution<Number>>::type
{
  if constexpr (std::is_integral_v<Number>) {
    return std::uniform_int_distribution<Number>(min, max);
  } else {
    return std::uniform_real_distribution<Number>(min, max);
  }
}

/**
 * @brief Generates a sequence of uniform random numbers
 * If sorted == true, the resulting sequence is strictly increasing
 */
template <template <typename...> class Container = std::vector, typename Number>
Container<Number> uniform_random_sequence(int length, Number min, Number max, bool sorted = false, bool uniq = false)
{
  if (std::is_integral_v<Number>) {
    assert(length <= max - min + 1);
  }

  std::mt19937 engine(0);
  auto dist = get_uniform_dist<Number>(min, max);

  std::vector<Number> vec;
  if (std::is_integral_v<Number> && uniq) // sequence of unique integers
  {
    std::vector<Number> tmp;
    for (int i = min; i <= max; ++i) {
      tmp.push_back(i);
    }
    std::shuffle(tmp.begin(), tmp.end(), engine);
    std::copy(tmp.begin(), tmp.begin() + length, std::back_inserter(vec));
  } else {
    for (int i = 0; i != length; ++i) {
      vec.emplace_back(dist(engine));
    }
  }
  if (sorted) {
    std::sort(vec.begin(), vec.end());
  }
  return Container(vec.begin(), vec.end());
}

#endif /* RANDOM_NUMBER_H */