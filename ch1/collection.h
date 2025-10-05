#ifndef COLLECTION__H
#define COLLECTION__H
#include <cstddef>
#include <stdexcept>
using namespace std;

template <typename Object>
class Collection
{
  Object* mData = nullptr;
  size_t mSize = 0;

public:
  bool isEmpty() const
  {
    return mSize == 0;
  }
  void makeEmpty()
  {
    if (!mData) {
      return;
    }
    delete[] mData;
    mData = nullptr;
    mSize = 0;
  }
  void insert(const Object& obj)
  {
    Object* tmp = new Object[mSize + 1];
    for (size_t i = 0; i != mSize; ++i) {
      tmp[i] = mData[i];
    }
    tmp[mSize] = obj;
    delete[] mData;
    mData = tmp;
    ++mSize;
  }

  void remove(const Object& obj)
  {
    Object* pObj = find(obj);
    if (!pObj) {
      throw invalid_argument("Remove Failed");
    }

    Object* tmp = new Object[mSize - 1];
    for (size_t i = 0, j = 0; i != mSize; ++i) {
      if (mData + i == pObj) {
        continue;
      }
      tmp[j] = mData[i];
      ++j;
    }
    delete[] mData;
    mData = tmp;
    --mSize;
  }

  bool contains(const Object& obj) const
  {
    return find(obj) != nullptr;
  }

private:
  Object* find(const Object& obj) const
  {
    for (size_t i = 0; i != mSize; ++i) {
      if (mData[i] == obj) {
        return mData + i;
      }
    }
    return nullptr;
  }
};

#endif /* COLLECTION__H */