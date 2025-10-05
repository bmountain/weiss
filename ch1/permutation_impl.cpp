#include "permutation_impl.h"
#include <print>
#include <string>

void permute(const std::string& str)
{
  permute_rec(str, 0, str.size() - 1);
}

void permute_rec(const std::string& str, int low, int high)
{
  // print characters with index 0, ..., low - 1
  std::print("{}", str.substr(0, low));
}