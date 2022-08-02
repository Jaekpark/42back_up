#ifndef _FT_MAKE_PAIR_HPP
#define _FT_MAKE_PAIR_HPP

#include "../config.hpp"
#include "../utility/pair.hpp"

// namespace_start
_BEGIN_NAMESPACE_FT

template <class T1, class T2>
ft::pair<T1, T2> make_pair(T1 x, T2 y) {
  return ft::pair<T1, T2>(x, y);
};
// namespace_end
_END_NAMESPACE_FT
#endif