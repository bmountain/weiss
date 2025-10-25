#ifndef SET_H
#define SET_H

#include "ParentTree.h"

template <typename Comparable>
class Set
{
  ParentTree<Comparable> tree;

public:
  void insert(const Comparable& x)
  {
    tree.insert(x);
  }
  void remove(const Comparable& x)
  {
    tree.remove(x);
  }

  using iterator = ParentTree<Comparable>::iterator;
  iterator begin()
  {
    return tree.begin();
  }
  iterator end()
  {
    return tree.end();
  }
};

#endif /* SET_H */