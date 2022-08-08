#ifndef _FT_NULLPTR_T_HPP
#define _FT_NULLPTR_T_HPP

#include "../config.hpp"
_BEGIN_NAMESPACE_FT
// namespace_start
class nullptr_t {
 public:
  template <class T>
  operator T*() const {
    return (0);
  }

  template <class C, class T>
  operator T C::*() const {
    return (0);
  }

 private:
  void operator&() const;

} ft_nullptr = {};
// namespace_end
_END_NAMESPACE_FT
#endif