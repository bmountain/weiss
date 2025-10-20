#ifndef BINARY_SEARCH_ITERATOR_H
#define BINARY_SEARCH_ITERATOR_H

#include "BaseTreeIterator.h"
#include <stack>

/**
 * Standard node of binary trees.
 */
template <typename Comparable>
struct BinarySearchNode : public BaseTreeNode<Comparable, BinarySearchNode<Comparable>>
{
  using BaseTreeNode<Comparable, BinarySearchNode<Comparable>>::BaseTreeNode;
};

/**
 * Iterator of binary trees that traverse with stack of path.
 */
template <typename Comparable, template <typename> typename Node>
class BinarySearchIterator : public BaseTreeIterator<Comparable, Node>
{
public:
  using node_type = BaseTreeIterator<Comparable, Node>::node_type;
  using iterator = BinarySearchIterator<Comparable, Node>;
  BinarySearchIterator(node_type* node)
  : BaseTreeIterator<Comparable, Node>(node)
  {
    push_left(node);
  }
  iterator& operator++() override
  {
    if (!current) {
      return *this;
    }

    if (current->right) {
      push_left(this->current->right.get());
      return *this;
    }

    if (st.empty()) {
      current = nullptr;
      return *this;
    } else {
      current = st.top();
      st.pop();
      return *this;
    }
  }
  using Base = BaseTreeIterator<Comparable, Node>;
  using Base::operator*;
  using Base::operator==;
  using Base::operator!=;

private:
  using Base::current;
  std::stack<node_type*> st;
  void push_left(node_type* node)
  {
    if (!node) {
      return;
    }
    while (node) {
      st.push(node);
      node = node->left.get();
    }
    current = st.top();
    st.pop();
  }
};

#endif /* BINARY_SEARCH_ITERATOR_H */
