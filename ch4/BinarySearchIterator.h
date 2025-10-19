#ifndef BINARY_SEARCH_ITERATOR_H
#define BINARY_SEARCH_ITERATOR_H

#include "BaseTreeIterator.h"
#include "BinarySearchNode.h"
#include <stack>

template <typename Object, typename Node>
class BinarySearchIterator : public BaseTreeIterator<Object, Node>
{
public:
  BinarySearchIterator(Node* node)
  : BaseTreeIterator<Object, Node>(node)
  {
    push_left(node);
  }
  BinarySearchIterator& operator++() override;
  using Base = BaseTreeIterator<Object, Node>;
  using Base::operator*;
  using Base::operator==;
  using Base::operator!=;

private:
  using Base::current;
  std::stack<Node*> st;
  void push_left(Node* node);
};

template <typename Object, typename Node>
BinarySearchIterator<Object, Node>& BinarySearchIterator<Object, Node>::operator++()
{
  if (!this->current) {
    return *this;
  }

  if (this->current->right) {
    push_left(this->current->right.get());
    return *this;
  }

  if (st.empty()) {
    this->current = nullptr;
    return *this;
  } else {
    this->current = st.top();
    st.pop();
    return *this;
  }
}

template <typename Object, typename Node>
void BinarySearchIterator<Object, Node>::push_left(Node* node)
{
  if (!node) {
    return;
  }
  while (node) {
    st.push(node);
    node = node->left.get();
  }
  this->current = st.top();
  st.pop();
}
#endif /* BINARY_SEARCH_ITERATOR_H */
