/**
 * @brief Base class of binary search tree
 */
#ifndef BASE_BINARY_TREE_H
#define BASE_BINARY_TREE_H

#include "BaseTreeIterator.h"
#include "BaseTreeNode.h"
#include <iostream>
#include <memory>
#include <print>
#include <stdexcept>

/**
 * Base class of Binary search tree, from which balanced trees would be derived.
 */
template <typename Comparable, typename Node>
class BaseTree
{
public:
  // special member functions
  BaseTree() = default;
  virtual ~BaseTree() = default;

  // accesser
  using iterator = BaseTreeIterator<Comparable, Node>;

  iterator begin()
  {
    return iterator(this->root.get());
  }

  iterator end()
  {
    return iterator(nullptr);
  }

  Comparable findMin() const;
  Comparable findMax() const;
  bool contains(const Comparable& x) const;
  bool empty() const;
  void printTree(std::ostream& os = std::cout) const;

  // mutator
  void insert(const Comparable& x)
  {
    insert(x, this->root);
  }
  void remove(const Comparable& x)
  {
    remove(x, this->root);
  }

protected:
  std::unique_ptr<Node> root = nullptr;

  void insert(const Comparable& x, std::unique_ptr<Node>& node)
  {
    if (!node) {
      node = std::make_unique<Node>(x);
      return;
    }
    if (x < node->element) {
      insert(x, node->left);
    }
    if (x > node->element) {
      insert(x, node->right);
    }
  }

  void remove(const Comparable& x, std::unique_ptr<Node>& node)
  {
    if (!node) {
      return;
    }
    if (x < node->element) {
      remove(x, node->left);
      return;
    }
    if (x > node->element) {
      remove(x, node->right);
      return;
    }

    if (node->right) {
      node->element = this->findMin(node->right)->element;
      remove(node->element, node->right);
      return;
    }
    node = std::move(node->left);
  }

  Node* findMin(const std::unique_ptr<Node>&) const;
  Node* findMax(const std::unique_ptr<Node>&) const;
  bool contains(const Comparable&, const std::unique_ptr<Node>&) const;
  void printTree(std::ostream&, const std::unique_ptr<Node>&) const;
};

/*************** private member functions ***************/

template <typename Comparable, typename Node>
Node* BaseTree<Comparable, Node>::findMin(const std::unique_ptr<Node>& node) const
{
  if (!node) {
    return nullptr;
  }
  if (node->left) {
    return findMin(node->left);
  }
  return node.get();
}

template <typename Comparable, typename Node>
Node* BaseTree<Comparable, Node>::findMax(const std::unique_ptr<Node>& node) const
{
  if (!node) {
    return nullptr;
  }
  if (node->right) {
    return findMax(node->right);
  }
  return node.get();
}

template <typename Comparable, typename Node>
bool BaseTree<Comparable, Node>::contains(const Comparable& x, const std::unique_ptr<Node>& node) const
{
  if (!node) {
    return false;
  }
  if (x < node->element) {
    return contains(x, node->left);
  }
  if (x > node->element) {
    return contains(x, node->right);
  }
  return true;
}

template <typename Comparable, typename Node>
void BaseTree<Comparable, Node>::printTree(std::ostream& os, const std::unique_ptr<Node>& node) const
{
  if (!node) {
    return;
  }
  printTree(os, node->left);
  std::println(os, "{}", node->element);
  printTree(os, node->right);
}

/*************** public member functions ***************/

template <typename Comparable, typename Node>
Comparable BaseTree<Comparable, Node>::findMin() const
{
  if (!root) {
    throw std::out_of_range("Error: Empty tree");
  }
  return findMin(root)->element;
}

template <typename Comparable, typename Node>
Comparable BaseTree<Comparable, Node>::findMax() const
{
  if (!root) {
    throw std::out_of_range("Error: Empty tree");
  }
  return findMax(root)->element;
}

template <typename Comparable, typename Node>
bool BaseTree<Comparable, Node>::contains(const Comparable& x) const
{
  return contains(x, root);
}

template <typename Comparable, typename Node>
bool BaseTree<Comparable, Node>::empty() const
{
  return !root;
}

template <typename Comparable, typename Node>
void BaseTree<Comparable, Node>::printTree(std::ostream& os) const
{
  printTree(os, root);
}

#endif /* BASE_BINARY_TREE_H */