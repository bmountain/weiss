/**
 * Binary search tree implementation
 */
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "BaseTree.h"
#include "StackIterator.h"

/**
 * Standard implementation of binary tree.
 * Assumes that an iterator is constructed from a row pointer to a node.
 */
template <typename Comparable, template <typename> typename Node, template <typename, template <typename> typename> typename Iterator>
class StackTree : public BaseTree<Comparable, Node, Iterator>
{

public:
  using node_type = Node<Comparable>;
  using iterator = Iterator<Comparable, Node>;
  iterator begin()
  {
    return iterator(this->root.get());
  }

  iterator end()
  {
    return iterator(nullptr);
  }

private:
  template <typename C, template <typename> typename N>
  friend class Iterator;
};

#endif /* BINARY_SEARCH_TREE_H */