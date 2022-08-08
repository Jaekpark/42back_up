#ifndef _FT_UTILITY_HPP
#define _FT_UTILITY_HPP

#include "../config.hpp"
_BEGIN_NAMESPACE_FT

template <class Arg1, class Arg2, class Result>
struct binary_function {
  typedef Arg1 first_argument_type;
  typedef Arg2 second_argument_type;
  typedef Result result_type;
};
template <class T>
struct less : public binary_function<T, T, bool> {
  bool operator()(const T& x, const T& y) const { return (x < y); }
};

_END_NAMESPACE_FT
#endif