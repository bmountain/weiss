#include "selection.h"
#include <chrono>
#include <print>
#include <random>
#include <vector>
using namespace std::chrono;

std::vector<int> generateVector(std::size_t k, std::mt19937& engine)
{
  static std::uniform_int_distribution dist{};

  std::vector<int> vec;
  for (std::size_t i = 0; i != k; ++i) {
    vec.push_back(dist(engine));
  }
  return vec;
}

int main()
{
  std::mt19937 engine{0};
  std::vector<std::size_t> numElements;
  for (int i = 1; i != 10; ++i) {
    numElements.push_back(std::pow(10, i));
  }

  for (const auto& num : numElements) {
    auto vec = generateVector(num, engine);
    system_clock::time_point beg = system_clock::now();
    selection(vec, vec.size() / 2);
    system_clock::time_point end = system_clock::now();
    std::println("#{}: {}", num, std::chrono::duration_cast<milliseconds>(end - beg));
  }
}