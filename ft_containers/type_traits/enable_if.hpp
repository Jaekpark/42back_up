#ifndef _FT_ENABLE_IF_HPP
#define _FT_ENABLE_IF_HPP

#include "../config.hpp"
#include "../type_traits/is_integral.hpp"
// namespace_start
_BEGIN_NAMESPACE_FT
template <bool, class T = void>
struct enable_if {};
template <class T>
struct enable_if<true, T> {
  typedef T type;
};
// namespace_end
_END_NAMESPACE_FT

#endif