#ifndef _FT_PAIR_HPP
#define _FT_PAIR_HPP

#include "../config.hpp"
// namespace_start
_BEGIN_NAMESPACE_FT
template <class T1, class T2>
struct pair {
 public:
  typedef T1 first_type;
  typedef T2 second_type;

  first_type first;
  second_type second;
  // default_constructor
  pair() : first(), second() {}
  pair(const pair<T1, T2>& pair) : first(pair.first), second(pair.second) {}
  explicit pair(const first_type& x, const second_type& y)
      : first(x), second(y) {}
  // copy_constructor
  // destructor
  ~pair(void) {}
  pair& operator=(const pair& x) {
    this->first = x.first;
    this->second = x.second;
    return *this;
  }
};
template <class T1, class T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return lhs.first == rhs.first && lhs.second == rhs.second;
}
template <class T1, class T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return !(lhs == rhs);
}
template <class T1, class T2>
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return lhs.first < rhs.first ||
         (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}
template <class T1, class T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return !(rhs < lhs);
}
template <class T1, class T2>
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return rhs < lhs;
}
template <class T1, class T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return !(lhs < rhs);
}

// namespace_end
_END_NAMESPACE_FT

#endif