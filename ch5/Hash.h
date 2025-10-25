#ifndef HASH_H
#define HASH_H

#include <string>

template <typename Object>
class hash;

template <>
class hash<std::string>
{
public:
  size_t operator()(const std::string& str) const
  {
    size_t hv = 0;
    for (const auto& c : str) {
      hv += c;
    }
    return hv;
  }
};

template <>
class hash<size_t>
{
public:
  size_t operator()(const size_t n) const
  {
    return n;
  }
};

#endif /* HASH_H */