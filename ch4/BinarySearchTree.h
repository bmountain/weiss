/**
 * Binary search tree implementation
 */
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "BaseTree.h"
#include "BinarySearchIterator.h"
#include "BinarySearchNode.h"

/*************** Binary Search Tree ***************/

template <typename Comparable>
class BinarySearchTree : public BaseTree<Comparable, BinarySearchNode<Comparable>>
{
  using Node = BinarySearchNode<Comparable>;

public:
  using iterator = BinarySearchIterator<Comparable, Node>;
  iterator begin()
  {
    return iterator(this->root.get());
  }

  iterator end()
  {
    return iterator(nullptr);
  }

private:
  friend class BinarySearchIterator<Comparable, Node>;
};

#endif /* BINARY_SEARCH_TREE_H */