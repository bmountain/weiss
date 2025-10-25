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
    for (auto& item : table) {
      item.state = State::Empty;
    }
  }

  bool contains(const Object& obj) const override
  {
    return std::find_if(table.begin(),
                        table.end(),
                        [obj](Cell cell)
                        {
                          return cell.element == obj && cell.state == State::Active;
                        })
           != table.end();
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
    return true;
  }

  void clear() override
  {
    size_t orgSize = table.size();
    table.clear();
    table.resize(orgSize);
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

  bool isActive(size_t pos)
  {
    return table[pos].state == State::Active;
  }

  bool insertImpl(Object&& obj)
  {
    size_t pos = findPos(obj);
    if (table[pos].state != State::Empty) {
      return false;
    }
    Cell& cell = table[pos];
    cell.element = std::move(obj);
    cell.state = State::Active;
    if (++currentSize > table.size() / 2) {
      rehash();
    }
    return true;
  }

  size_t findPos(const Object& obj)
  {
    size_t pos = calcHashValue(obj);
    size_t offset = 1;
    while (table[pos].state != State::Empty && table[pos].element != obj) {
      pos += offset;
      offset += 2;
      if (offset >= table.size()) {
        pos %= table.size();
      }
    }
    return pos;
  }

  void rehash()
  {
    std::vector<Cell> old = table;
    table.clear();
    table.resize(old.size() * 2);
    for (const auto& cell : old) {
      insert(cell.element);
    }
  }

  template <typename T>
  bool insertImpl(T&& obj)
  {
    size_t pos = findPos(obj);
    if (table[pos].state != State::Empty) {
      return false;
    }
    Cell& cell = table[pos];
    cell.element = std::forward<T>(obj);
    cell.state = State::Active;
    if (++currentSize > table.size()) {
      rehash();
    }
    return true;
  }
};

#endif /* HASH_TABLE_H */