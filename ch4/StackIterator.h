#ifndef STACK_SEARCH_ITERATOR_H
#define STACK_SEARCH_ITERATOR_H

#include "BaseTreeIterator.h"
#include <stack>

/**
 * Iterator of binary trees that traverse with stack of path.
 */
template <typename Comparable, template <typename> typename Node>
class StackIterator : public BaseIterator<Comparable, Node>
{
public:
  using node_type = BaseIterator<Comparable, Node>::node_type;
  using iterator = StackIterator<Comparable, Node>;
  StackIterator(node_type* node)
  : BaseIterator<Comparable, Node>(node)
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
  using Base = BaseIterator<Comparable, Node>;
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

#endif /* STACK_SEARCH_ITERATOR_H */
