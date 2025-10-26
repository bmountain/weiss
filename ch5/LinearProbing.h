#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include "HashTable.h"

template <typename Object>
class LinearHashTable : public HashTable<Object>
{
public:
  LinearHashTable(size_t ts = 100, hash<Object> h1 = {})
  : HashTable<Object>{ts, h1}
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
  /**
   * Find a cell that either contais obj or can store obj
   */
  virtual size_t findPos(const Object& obj) const override
  {
    size_t pos = calcHashValue(obj);
    while (table[pos].state == Base::State::Active && table[pos].element != obj) {
      ++pos;
      if (pos >= table.size()) {
        pos %= table.size();
      }
    }
    return pos;
  }
};
#endif /* LINEAR_PROBING_H */