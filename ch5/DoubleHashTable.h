#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

#include "HashTable.h"

template <typename Object>
class DoubleHashTable : public HashTable<Object>
{
public:
  DoubleHashTable(size_t ts = 100, hash<Object> h1 = {}, double_hash<Object> h2 = {})
  : HashTable<Object>{ts, h1}
  , hashFunction2(h2)
  {
  }

  using Base = HashTable<Object>;
  using Base::calcHashValue;
  using Base::clear;
  using Base::contains;
  using Base::hashFunction;
  using Base::insert;
  using Base::remove;
  using Base::State;
  using Base::table;

private:
  double_hash<Object> hashFunction2;

  size_t calcHashValue2(const Object& object) const
  {
    return table.size() - hashFunction2(object) % table.size();
  }

  /**
   * Find a cell that either contais obj or can store obj
   */
  virtual size_t findPos(const Object& obj) const override
  {
    size_t pos = calcHashValue(obj);
    size_t offset = calcHashValue2(obj);
    while (table[pos].state == Base::State::Active && table[pos].element != obj) {
      pos += offset;
      if (pos >= table.size()) {
        pos %= table.size();
      }
    }
    return pos;
  }
};

#endif /* DOUBLE_HASH_TABLE_H */