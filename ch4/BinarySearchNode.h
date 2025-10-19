#ifndef BINARY_SEARCH_NODE_H
#define BINARY_SEARCH_NODE_H

#include "BaseTree.h"

template <typename Comparable>
struct BinarySearchNode : public BaseTreeNode<Comparable, BinarySearchNode<Comparable>>
{
  using BaseTreeNode<Comparable, BinarySearchNode<Comparable>>::BaseTreeNode;
};

#endif /* BINARY_SEARCH_NODE_H */