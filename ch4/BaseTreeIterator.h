#ifndef BASE_ITERATOR_H
#define BASE_ITERATOR_H

#include <memory>
/**
 * Element of binary search trees are totally ordered.
 * Nodes in trees have element, and pointers to left and right node.
 * Minimal implementation of node is as follows.
 *
 * A concrete class of node would be derived from this class.
 * This is CRTP.
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

/**
 * Base class of binary trees.
 * operator++ would be overridden.
 */
template <typename Comparable, template <typename> typename Node>
class BaseTreeIterator
{
public:
  using node_type = Node<Comparable>;
  BaseTreeIterator(node_type* node)
  : current{node}
  {
  }
  virtual ~BaseTreeIterator() = default;
  virtual BaseTreeIterator& operator++() = 0;
  Comparable operator*()
  {
    return this->current->element;
  }
  bool operator==(const BaseTreeIterator& rhs)
  {
    return this->current == rhs.current;
  }
  bool operator!=(const BaseTreeIterator& rhs)
  {
    return !(*this == rhs);
  }

protected:
  node_type* current;
};

#endif /* BASE_ITERATOR_H */