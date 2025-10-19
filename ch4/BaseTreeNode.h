#ifndef BASE_BINARY_TREE_NODE_H
#define BASE_BINARY_TREE_NODE_H

#include <memory>

/**
 * Objects stored in binary search trees are totally ordered.
 * Nodes in trees have element, and unique_ptr to left and right node.
 * Minimal implementation of node is as follows.
 */
template <typename Comparable, typename DerivedNode>
struct BaseTreeNode
{
  Comparable element;
  std::unique_ptr<DerivedNode> left = nullptr;
  std::unique_ptr<DerivedNode> right = nullptr;
  BaseTreeNode(Comparable pElement)
  : element(pElement)
  {
  }
};

#endif /* BASE_BINARY_TREE_NODE_H */