#ifndef BASE_ITERATOR_H
#define BASE_ITERATOR_H

template <typename Object, typename Node>
class BaseTreeIterator
{
public:
  BaseTreeIterator(Node* node)
  : current{node}
  {
  }
  virtual BaseTreeIterator& operator++() = 0;
  Object operator*()
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
  Node* current;
};

#endif /* BASE_ITERATOR_H */