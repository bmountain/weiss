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
struct BaseNode
{
  Comparable element;
  std::unique_ptr<DerivedNode> left = nullptr;
  std::unique_ptr<DerivedNode> right = nullptr;
  BaseNode(Comparable pElement)
  : element(pElement)
  {
  }
};

/**
 * Standard node of binary trees
 */
template <typename Comparable>
struct BinaryTreeNode : public BaseNode<Comparable, BinaryTreeNode<Comparable>>
{
  using BaseNode<Comparable, BinaryTreeNode<Comparable>>::BaseNode;
};

/**
 * Base class of binary trees.
 * operator++ would be overridden.
 */
template <typename Comparable, template <typename> typename Node>
class BaseIterator
{
public:
  using node_type = Node<Comparable>;
  BaseIterator(node_type* node)
  : current{node}
  {
  }
  virtual ~BaseIterator() = default;
  virtual BaseIterator& operator++() = 0;
  Comparable operator*()
  {
    return this->current->element;
  }
  bool operator==(const BaseIterator& rhs)
  {
    return this->current == rhs.current;
  }
  bool operator!=(const BaseIterator& rhs)
  {
    return !(*this == rhs);
  }

protected:
  node_type* current;
};

#endif /* BASE_ITERATOR_H */