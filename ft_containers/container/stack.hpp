#ifndef _FT_STACK_HPP
#define _FT_STACK_HPP

#include "../config.hpp"
#include "../utility/nullptr_t.hpp"
#include "./vector.hpp"

_BEGIN_NAMESPACE_FT

template <class T, class Container = ft::vector<T> >
class stack {
 public:
  typedef Container container_type;
  typedef typename Container::value_type value_type;
  typedef typename Container::size_type size_type;
  typedef typename Container::reference reference;
  typedef typename Container::const_reference const_reference;

 protected:
  container_type _container;

 public:
  /* ---------------------------------------------------------------- */
  /*                            CONSTRUCTOR                           */
  /* ---------------------------------------------------------------- */
  explicit stack(const container_type& cont = container_type())
      : _container(cont) {}

  stack(const stack& other) : _container(other._container) {}

  stack& operator=(const stack& other) {
    _container = other._container;
    return (*this);
  }
  /* ---------------------------------------------------------------- */
  /*                         MEMBER FUNCTIONS                         */
  /* ---------------------------------------------------------------- */
  bool empty() const { return (_container.empty()); }
  size_type size() const { return (_container.size()); }
  value_type& top() { return (_container.back()); }
  const value_type& top() const { return (_container.back()); }
  void push(const value_type& val) { _container.push_back(val); }
  void pop() { _container.pop_back(); }
  /* ---------------------------------------------------------------- */
  /*                       NON-MEMBER FUNCTIONS                       */
  /* ---------------------------------------------------------------- */
  template <class T1, class C1>
  friend bool operator==(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
  template <class T1, class C1>
  friend bool operator!=(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
  template <class T1, class C1>
  friend bool operator<(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
  template <class T1, class C1>
  friend bool operator<=(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
  template <class T1, class C1>
  friend bool operator>(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
  template <class T1, class C1>
  friend bool operator>=(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
};
template <class T1, class C1>
bool operator==(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs) {
  return (lhs._container == rhs._container);
}
template <class T1, class C1>
bool operator!=(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs) {
  return !(lhs._container == rhs._container);
}
template <class T1, class C1>
bool operator<(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs) {
  return (lhs._container < rhs._container);
}
template <class T1, class C1>
bool operator<=(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs) {
  return !(rhs._container < lhs._container);
}
template <class T1, class C1>
bool operator>(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs) {
  return (rhs._container < lhs._container);
}
template <class T1, class C1>
bool operator>=(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs) {
  return !(lhs._container < rhs._container);
}

_END_NAMESPACE_FT
#endif