/**
 * Implements hash table by separated chaining
 */
#ifndef SEPARATED_CHAINING_H
#define SEPARATED_CHAINING_H

#include "PrimeNumber.h"
#include <algorithm>
#include <forward_list>
#include <functional>
#include <string>
#include <vector>

template <typename Object>
class SeparatedChaining
{
public:
  explicit SeparatedChaining(size_t tableSize, hash<Object> hf)
  : table(nextPrime(tableSize))
  , hashFunc(hf)
  {
  }

  bool contains(const Object& obj) const
  {
    const std::forward_list<Object>& row = table[calcHashValue(obj)];
    return std::find(row.begin(), row.end(), obj) != row.end();
  }

  bool insert(const Object& obj)
  {
    return insertImpl(obj);
  }

  bool insert(Object&& obj)
  {
    return insertImpl(obj);
  }

  bool remove(const Object& obj)
  {
    if (contains(obj)) {
      table[calcHashValue(obj)].remove(obj);
      --currentSize;
      return true;
    } else {
      return false;
    }
  }

  size_t getCollisionCount() const
  {
    return collisionCount;
  }

private:
  size_t currentSize = 0;
  std::vector<std::forward_list<Object>> table;
  hash<Object> hashFunc;
  size_t collisionCount{};
  size_t calcHashValue(const Object& obj) const
  {
    return hashFunc(obj) % table.size();
  }
  void rehash()
  {
    const auto oldtable = table;
    table.clear();
    table.resize(nextPrime(oldtable.size()));
    for (const auto& row : table) {
      for (const auto& item : row) {
        table[calcHashValue(item)].push_front(item);
      }
    }
  }

  template <typename T>
  bool insertImpl(T&& obj)
  {
    if (contains(obj)) {
      return false;
    } else {
      size_t hv = calcHashValue(obj);
      if (!table[hv].empty()) {
        ++collisionCount;
      }
      table[hv].emplace_front(std::move(obj));
      if (++currentSize > table.size()) {
        rehash();
      }
      return true;
    }
  }
};

#endif /* SEPARATED_CHAINING_H */