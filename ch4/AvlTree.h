#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "BaseTree.h"
#include "BaseTreeIterator.h"
#include <numeric>

/**
 * AVL tree node
 */
template <typename Comparable>
struct AvlNode : public BaseNode<Comparable, AvlNode<Comparable>>
{
  AvlNode<Comparable>* parent = nullptr;
  int height = 0;
};

/**
 * AVL tree
 * Node needs to have the member variable int height
 */
template <typename Comparable, template <typename> typename Node, template <typename, template <typename> typename> typename Iterator>
class AvlTree : public BaseTree<Comparable, Node, Iterator>
{
public:
  using node_type = Node<Comparable>;
  using iterator = Iterator<Comparable, Node>;
  using Base = BaseTree<Comparable, Node, Iterator>;

  using Base::findMax;
  using Base::findMin;

  iterator begin()
  {
    return iterator(this->root.get());
  }

  iterator end()
  {
    return iterator(nullptr);
  }

  void insert(const Comparable& x) override
  {
    insert(x, this->root, nullptr);
  }

  void remove(const Comparable& x) override
  {
    remove(x, this->root);
  }

private:
  void insert(const Comparable& x, std::unique_ptr<node_type>& node, const std::unique_ptr<node_type>& parent)
  {
    if (!node) {
      node = std::make_unique<node_type>(x);
      node->parent = parent.get();
    }
    if (x < node->element) {
      insert(x, node->left, node);
    }
    if (x > node->element) {
      insert(x, node->right, node);
    }
    balance(node);
  }

  void remove(const Comparable& x, std::unique_ptr<node_type>& node) override
  {
    if (!node) {
      return;
    }
    if (x < node->element) {
      remove(x, node->left);
    } else if (x > node->element) {
      remove(x, node->right);
    } else if (node->left && node->right) {
      node->element = this->findMin(node->right)->element;
      remove(node->element, node->right);
    } else if (node->left || node->right) {
      node->element = node->left ? node->left->element : node->right->element;
      remove(node->element, node->left ? node->left : node->right);
    } else {
      node = nullptr;
    }
    balance(node);
  }

  void balance(std::unique_ptr<node_type>& node)
  {
    if (!node) {
      return;
    }
    if (height(node->left) - height(node->right) > 1) {
      if (height(node->left->left) > height(node->left->right)) {
        singleRotateLeft(node);
      } else {
        doubleRotateLeft(node);
      }
    } else if (height(node->right) - height(node->left) > 1) {
      if (height(node->right->right) > height(node->right->left)) {
        singleRotateRight(node);
      } else {
        doubleRotateRight(node);
      }
    }
  }

  void singleRotateLeft(std::unique_ptr<node_type>& node)
  {
    std::unique_ptr<node_type>& child = node->left;
    child->parent = node->parent;

    child->right->parent = node.get();
    node->left = std::move(child->right);
    child->right = nullptr;
    updateHeight(node);

    node->parent = child.get();
    child->right = std::move(node);
    node = nullptr;
    updateHeight(child);

    node = std::move(child);
  }

  void singleRotateRight(std::unique_ptr<node_type>& node)
  {
    std::unique_ptr<node_type>& child = node->right;
    child->parent = node->parent;

    child->left->parent = node.get();
    node->right = std::move(child->left);
    child->left = nullptr;
    updateHeight(node);

    node->parent = child.get();
    child->left = std::move(node);
    node = nullptr;
    updateHeight(child);

    node = std::move(child);
  }

  void doubleRotateLeft(std::unique_ptr<node_type>& node)
  {
    singleRotateRight(node->left);
    singleRotateLeft(node);
  }

  void doubleRotateRight(std::unique_ptr<node_type>& node)
  {
    singleRotateLeft(node->right);
    singleRotateRight(node);
  }

  int height(std::unique_ptr<node_type>& node) const
  {
    return node ? node->height : -1;
  }

  void updateHeight(std::unique_ptr<node_type>& node)
  {
    node->height = std::max(height(node->left), height(node->right)) + 1;
  }

  template <typename C, template <typename> typename N>
  friend class Iterator;
};

#endif /* AVL_TREE_H */