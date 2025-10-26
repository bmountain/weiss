#include "DoubleHashTable.h"
#include "HashTable.h"
#include "LinearProbing.h"
#include "SeparatedChaining.h"
#include "Words.h"
#include "measure.h"
#include <chrono>
#include <print>
#include <random>

std::vector<std::string> get_words()
{
  auto words = word_list();
  std::shuffle(words.begin(), words.end(), std::default_random_engine{0});
  return words;
}

auto words = get_words();

template <typename Table>
std::pair<size_t, double> collision(Table table)
{
  using clock = std::chrono::steady_clock;
  auto start = clock::now();
  for (auto word : words) {
    table.insert(word);
  }
  auto end = clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
  return std::make_pair(table.getCollisionCount(), duration.count());
}

int main()
{
  SeparatedChaining<std::string> chain{words.size(), hash<std::string>{}};
  auto ret = collision(chain);
  std::println("Separated Chaining: {} ({})", ret.first, ret.second);

  LinearHashTable<std::string> linear{words.size(), hash<std::string>{}};
  ret = collision(linear);
  std::println("Linear Probing: {} ({})", ret.first, ret.second);

  HashTable<std::string> quad{words.size(), hash<std::string>{}};
  ret = collision(quad);
  std::println("Quadratic Probing: {} ({})", ret.first, ret.second);

  DoubleHashTable<std::string> dbl{words.size(), hash<std::string>{}, double_hash<std::string>{}};
  ret = collision(dbl);
  std::println("Double Hash: {} ({})", ret.first, ret.second);
}