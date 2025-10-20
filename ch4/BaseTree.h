/**
 * @brief Base class of binary search tree
 */
#ifndef BASE_BINARY_TREE_H
#define BASE_BINARY_TREE_H

#include "BaseTreeIterator.h"
#include <iostream>
#include <memory>
#include <print>
#include <stdexcept>

/**
 * Base class of Binary search tree, from which balanced trees would be derived.
 */
template <typename Comparable, template <typename> typename Node, template <typename, template <typename> typename> typename Iterator>
class BaseTree
{
public:
  // special member functions
  BaseTree() = default;
  virtual ~BaseTree() = default;

  // accesser
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

  Comparable findMin() const
  {
    if (!root) {
      throw std::out_of_range("Error: Empty tree");
    }
    return findMin(root)->element;
  }

  Comparable findMax() const
  {
    if (!root) {
      throw std::out_of_range("Error: Empty tree");
    }
    return findMax(root)->element;
  }

  bool contains(const Comparable& x) const
  {
    return contains(x, root);
  }

  bool empty() const
  {
    return !root;
  }

  void printTree(std::ostream& os = std::cout) const
  {
    printTree(os, root);
  }

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
  std::unique_ptr<node_type> root = nullptr;

  void insert(const Comparable& x, std::unique_ptr<node_type>& node)
  {
    if (!node) {
      node = std::make_unique<node_type>(x);
      return;
    }
    if (x < node->element) {
      insert(x, node->left);
    }
    if (x > node->element) {
      insert(x, node->right);
    }
  }

  void remove(const Comparable& x, std::unique_ptr<node_type>& node)
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

  node_type* findMin(const std::unique_ptr<node_type>& node) const
  {
    if (!node) {
      return nullptr;
    }
    if (node->left) {
      return findMin(node->left);
    }
    return node.get();
  }

  node_type* findMax(const std::unique_ptr<node_type>& node) const
  {
    if (!node) {
      return nullptr;
    }
    if (node->right) {
      return findMax(node->right);
    }
    return node.get();
  }

  bool contains(const Comparable& x, const std::unique_ptr<node_type>& node) const
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

  void printTree(std::ostream& os, const std::unique_ptr<node_type>& node) const
  {
    if (!node) {
      return;
    }
    printTree(os, node->left);
    std::println(os, "{}", node->element);
    printTree(os, node->right);
  }
};

#endif /* BASE_BINARY_TREE_H */