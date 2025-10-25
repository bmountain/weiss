#ifndef MAP_H
#define MAP_H

#include "Set.h"
#include <utility>

template <typename Key, typename Value>
class Map : public StackIterator<std::pair<Key, Value>, BinarySearchNode<std::pair<Key, Value>>>
{
  Set<std::pair<Key, Value>> set;

public:
  using iterator = Set<std::pair<Key, Value>>::iterator;
  iterator begin()
  {
    return set.begin();
  }
  iterator end()
  {
    return set.end();
  }
  Value& operator[](const Key& key)
  {
  }
};

#endif /* MAP_H */