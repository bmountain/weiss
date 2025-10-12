#ifndef CH_3_H
#define CH_3_H

#include <list>
#include <memory>
#include <numeric>
#include <print>
#include <vector>

namespace ch3
{

void printLots(std::list<int>, std::list<int>);

template <typename Iterator, typename Object>
Iterator find(Iterator start, Iterator end, const Object& x)
{
  for (Iterator it = start; it != end; ++it) {
    if (*it == x) {
      return it;
    }
  }
  return end;
}

/**
 * @brief Returns the intersection of two sorted lists
 */
template <typename Object>
std::list<Object> getIntersection(const std::list<Object>& left, const std::list<Object>& right)
{
  auto lbegin = left.begin();
  auto lend = left.end();
  auto rend = right.end();
  auto rbegin = right.begin();

  std::list<Object> intersection;
  while (lbegin != lend || rbegin != rend) {
    if (*lbegin == *rbegin) {
      intersection.push_back(*lbegin);
      ++lbegin;
      ++rbegin;
      continue;
    } else if (*lbegin < *rbegin) {
      ++lbegin;
    } else {
      ++rbegin;
    }
  }

  return intersection;
}

/**
 * @brief Returns the union of two sorted lists
 */
template <typename Object>
std::list<Object> getUnion(const std::list<Object>& left, const std::list<Object>& right)
{
  auto lbegin = left.begin();
  auto lend = left.end();
  auto rend = right.end();
  auto rbegin = right.begin();

  std::list<Object> uni;
  while (lbegin != lend || rbegin != rend) {
    if (*lbegin == *rbegin) {
      uni.push_back(*lbegin);
      ++lbegin;
      ++rbegin;
      continue;
    } else if (*lbegin < *rbegin) {
      uni.push_back(*lbegin++);
    } else {
      uni.push_back(*rbegin++);
    }
  }

  return uni;
}

int josephas(int m, int n);

template <typename Object>
class list
{
public:
  struct Node
  {
    Node(Object object = Object{})
    : value{object} {};
    Node* prev = nullptr;
    Node* next = nullptr;
    Object value{};
  };

  class iterator
  {
    Node* node;

  public:
    friend class list<Object>;
    iterator(Node* node_ = nullptr)
    : node{node_}
    {
    }

    iterator(const iterator&) = default;
    iterator& operator=(const iterator&) = default;
    iterator operator++()
    {
      return node = node->next;
    }
    iterator operator++(int)
    {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    bool operator==(const iterator& other) const
    {
      return this->node == other.node;
    }
    bool operator!=(const iterator& other) const
    {
      return !(*this == other);
    }
    Object& operator*()
    {
      return node->value;
    }
  };

  ~list()
  {
    Node* current = head.node;
    while (current != nullptr) {
      Node* next = current->next;
      delete current;
      current = next;
    }
  }

  iterator begin() const
  {
    iterator ret = head;
    return ++ret;
  }

  iterator end() const
  {
    return iterator{};
  }

  iterator back() const
  {
    iterator current = head;
    while (current.node->next) {
      ++current;
    }
    return current;
  }

  void push_back(const Object& obj)
  {
    Node* newNode = new Node{obj};
    Node* bk = back().node;
    bk->next = newNode;
    newNode->prev = bk;
  }

  size_t size() const
  {
    size_t ret = 0;
    for (iterator current = head; current != end(); ++current) {
      ++ret;
    }
    return ret - 1;
  }

  void print() const
  {
    iterator current = head;
    ++current;
    while (current != end()) {
      std::print("{} ", *current);
      ++current;
    }
    std::println("");
  }

  bool contains(const Object& obj) const
  {
    iterator current = head;
    while (++current != end()) {
      if (*current == obj) {
        return true;
      }
    }
    return false;
  }

  bool insert(const Object& obj)
  {
    if (contains(obj)) {
      return false;
    }
    push_back(obj);
    return true;
  }

  void remove(const Object& obj) const
  {
    iterator current = head;
    while (current != end()) {
      if (*current == obj) {
        current.node->prev->next = current.node->next;
        current.node->next->prev = current.node->prev;
        delete current.node;
        return;
      }
      ++current;
    }
  }

private:
  iterator head{new Node{}};
};

} // namespace ch3

#endif /* CH_3_H */