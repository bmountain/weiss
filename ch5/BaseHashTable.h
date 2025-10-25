#ifndef BASE_HASH_TABLE_H
#define BASE_HASH_TABLE_H
#include "Hash.h"
#include "PrimeNumber.h"
#include <vector>

template <typename Object>
class BaseHashTable
{
public:
  virtual ~BaseHashTable() = default;

  virtual bool contains(const Object&) const = 0;
  virtual bool insert(const Object&) = 0;
  virtual bool insert(Object&&) = 0;
  virtual bool remove(const Object&) = 0;
  virtual void clear() = 0;

private:
  virtual void rehash() = 0;
};

#endif /* BASE_HASH_TABLE_H */