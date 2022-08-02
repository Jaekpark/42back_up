#ifndef _FT_REMOVE_CONST_HPP
#define _FT_REMOVE_CONST_HPP

#include "../config.hpp"

_BEGIN_NAMESPACE_FT

template <class T>
struct remove_const {
  typedef T type;
};
template <class T>
struct remove_const<const T> {
  typedef T type;
};

_END_NAMESPACE_FT

#endif