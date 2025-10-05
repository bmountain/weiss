#ifndef ORDERED_COLLECTION_H
#define ORDERED_COLLECTION_H

#include <algorithm>
#include <functional>
#include <optional>
#include <stdexcept>
#include <vector>

template <typename Comparable>
class OrderedCollection
{
  std::vector<Comparable> mData;

public:
  bool isEmpty() const
  {
    return mData.empty();
  }

  void makeEmpty()
  {
    mData.clear();
  }

  void insert(const Comparable& elem)
  {
    mData.push_back(elem);
  }

  void remove(const Comparable& elem)
  {
    auto it = std::find(mData.begin(), mData.end(), elem);
    mData.erase(it);
  }

  Comparable& findMin()
  {
    if (mData.empty()) {
      throw std::invalid_argument("Empty");
    }
    return *std::min_element(mData.begin(), mData.end(), std::less<Comparable>{});
  }

  Comparable& findMax()
  {
    if (mData.empty()) {
      throw std::invalid_argument("Empty");
    }
    return *std::max_element(mData.begin(), mData.end(), std::less<Comparable>{});
  }
};

#endif /* ORDERED_COLLECTION_H */