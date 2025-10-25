#ifndef BINARY_SEARCH_ITERATOR_H
#define BINARY_SEARCH_ITERATOR_H

#include "BaseTreeIterator.h"
#include <stack>

/**
 * Node with a pointer to the parent.
 */
template <typename Comparable>
struct ParentSearchNode : public BaseNode<Comparable, ParentSearchNode<Comparable>>
{
  ParentSearchNode<Comparable>* parent = nullptr;
};

/**
 * Iterator of binary trees that traverse with parent information
 */
template <typename Comparable, template <typename> typename Node>
class ParentIterator : public BaseIterator<Comparable, Node>
{
public:
  using Base = BaseIterator<Comparable, Node>;
  using node_type = Base::node_type;
  using iterator = ParentIterator<Comparable, Node>;

  ParentIterator(node_type* node)
  : Base{node}
  {
    go_left();
  }

  iterator& operator++() override
  {
    /**
     * Right node exists: go right one steap ahead and go left as long as possible
     * Other: Go to the first antecedant larget than current
     *
     * Note:
     * begin need to set current to the left most node
     * insertion need to set parents
     */
    if (!current) { // empty tree
      return *this;
    }
    if (current->right) {
      current = current->right.get();
      while (current->left) {
        current = current->left.get();
      }
      return *this;
    }
    if (!current->parent) { // traversal ends at root
      current = nullptr;
      return *this;
    }
    node_type* dest = current;
    while (dest->parent && dest->parent->element <= current->element) {
      dest = dest->parent;
    }
    if (!dest->parent) { // traversal ends
      current = nullptr;
      return *this;
    }
    current = dest->parent;
    return *this;
  }
  using Base::operator*;
  using Base::operator==;
  using Base::operator!=;

private:
  using Base::current;
  void go_left()
  {
    while (current && current->left) {
      current = current->left.get();
    }
  }
};

#endif /* BINARY_SEARCH_ITERATOR_H */
