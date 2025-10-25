#ifndef PARENT_SEARCH_TREE_H
#define PARENT_SEARCH_TREE_H

#include "BaseTree.h"
#include "ParentIterator.h"

/**
 * Tree with nodes that know parent
 */
template <typename Comparable,
          template <typename> typename Node = ParentSearchNode,
          template <typename, template <typename> typename> typename Iterator = ParentIterator>
class ParentTree : public BaseTree<Comparable, Node, Iterator>
{

public:
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

  void insert(const Comparable& x) override
  {
    insert(x, this->root, nullptr);
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
  }

  template <typename C, template <typename> typename N>
  friend class Iterator;
};

#endif /* PARENT_SEARCH_TREE */