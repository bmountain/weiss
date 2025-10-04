#ifndef SELECTION__H
#define SELECTION__H

#include <algorithm>
#include <functional>
#include <optional>
#include <vector>

/**
 * @brief Returns kth largest element
 */
template <typename Number>
std::optional<Number> selection(const std::vector<Number>& vec, std::size_t k)
{
  if (vec.size() < k) {
    return std::nullopt;
  }

  std::vector<Number> work{vec};
  std::sort(work.begin(), work.end(), std::greater<Number>{});
  return work[k - 1];
}

#endif /* SELECTION__H */