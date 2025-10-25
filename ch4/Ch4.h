#ifndef CH_4_H
#define CH_4_H

#include "AvlTree.h"
#include "BaseTree.h"
#include "ParentTree.h"
#include "Set.h"
#include "StackTree.h"

template <typename Comparable>
using StackSearchTree = StackTree<Comparable, BinaryTreeNode, StackIterator>;

template <typename Comparable>
using ParentSearchTree = ParentTree<Comparable, ParentSearchNode, ParentIterator>;

template <typename Comparable>
using AvlSearchTree = AvlTree<Comparable, AvlNode, ParentIterator>;

#endif /* CH_4_H */