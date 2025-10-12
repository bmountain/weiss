#include <vector>

/**
 * @brief Given an array a, determine if there exists i such that a[i] == i
 */
bool find_match(const std::vector<int>& vec)
{
  int l = 0, h = vec.size() - 1;
  while (l <= h) {
    int m = (l + h) / 2;
    if (m + 1 == vec[m]) {
      return true;
    }
    if (m + 1 < vec[m]) {
      h = m - 1;
      continue;
    }
    if (m + 1 > vec[m]) {
      l = m + 1;
      continue;
    }
  }
  return false;
}