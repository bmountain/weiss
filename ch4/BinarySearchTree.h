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
  void insert(const Comparable&) override;
  void remove(const Comparable&) override;
  iterator begin();
  iterator end();

private:
  void insert(const Comparable&, std::unique_ptr<Node>&) override;
  void remove(const Comparable&, std::unique_ptr<Node>&) override;

  friend class BinarySearchIterator<Comparable, Node>;
};

/*************** Implementation ***************/

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& x)
{
  insert(x, this->root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& x)
{
  remove(x, this->root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& x, std::unique_ptr<Node>& node)
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

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& x, std::unique_ptr<Node>& node)
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

template <typename Comparable>
BinarySearchTree<Comparable>::iterator BinarySearchTree<Comparable>::begin()
{
  return iterator(this->root.get());
}

template <typename Comparable>
BinarySearchTree<Comparable>::iterator BinarySearchTree<Comparable>::end()
{
  return iterator(nullptr);
}

#endif /* BINARY_SEARCH_TREE_H */