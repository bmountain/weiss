#include "count_binary_one.h"
#include <cstdlib>
#include <print>

int main(int argc, char** argv)
{
  if (argc < 2) {
    throw std::invalid_argument("Invalid Argument");
  }
  int n = atoi(argv[1]);
  std::println("binary format of {} has {} ones", n, count_binary_one(n));
}

int count_binary_one(int n)
{
  if (n <= 1) {
    return n;
  }
  int back = count_binary_one(n / 2);
  return n % 2 == 0 ? back : back + 1;
}