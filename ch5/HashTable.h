#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "BaseHashTable.h"
#include <algorithm>

template <typename Object>
class HashTable : public BaseHashTable<Object>
{
public:
  HashTable(size_t ts = nextPrime(100), hash<Object> h = hash<Object>{})
  : table(ts)
  , hashFunction(h)
  {
  }

  bool contains(const Object& obj) const override
  {
    return table[findPos(obj)].state == State::Active;
  }

  bool insert(const Object& obj) override
  {
    return insertImpl(obj);
  }

  bool insert(Object&& obj) override
  {
    return insertImpl(std::move(obj));
  }

  bool remove(const Object& obj) override
  {
    size_t pos = findPos(obj);
    if (!isActive(pos)) {
      return false;
    }
    table[pos].state = State::Deleted;
    --currentSize;
    return true;
  }

  void clear() override
  {
    for (auto& cell : table) {
      cell.state = State::Empty;
    }
    currentSize = 0;
  }

private:
  enum class State
  {
    Empty,
    Deleted,
    Active
  };

  struct Cell
  {
    State state = State::Empty;
    Object element{};
  };

  size_t currentSize = 0;
  std::vector<Cell> table;
  hash<Object> hashFunction;

  size_t calcHashValue(const Object& object) const
  {
    return hashFunction(object) % table.size();
  }

  bool isActive(size_t pos) const
  {
    return table[pos].state == State::Active;
  }

  /**
   * Find a cell that either contais obj or can store obj
   */
  size_t findPos(const Object& obj) const
  {
    size_t pos = calcHashValue(obj);
    size_t offset = 1;
    while (table[pos].state == State::Active && table[pos].element != obj) {
      pos += offset;
      offset += 2;
      if (pos >= table.size()) {
        pos -= table.size();
      }
    }
    return pos;
  }

  void rehash()
  {
    std::vector<Cell> old = table;
    table.clear();
    table.resize(nextPrime(old.size() * 2));
    currentSize = 0;
    for (auto& cell : old) {
      if (cell.state == State::Active) {
        insert(std::move(cell.element));
      }
    }
  }

  template <typename T>
  bool insertImpl(T&& obj)
  {
    size_t pos = findPos(obj);
    if (table[pos].state == State::Active) {
      return false;
    }

    if (table[pos].state == State::Empty) {
      ++currentSize;
    }

    Cell& cell = table[pos];
    cell.element = std::forward<T>(obj);
    cell.state = State::Active;
    if (currentSize * 2 > table.size()) {
      rehash();
    }
    return true;
  }
};

#endif /* HASH_TABLE_H */