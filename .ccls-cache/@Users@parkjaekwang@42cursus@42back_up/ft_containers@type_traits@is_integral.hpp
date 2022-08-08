#ifndef _FT_IS_INTEGRAL_HPP
#define _FT_IS_INTEGRAL_HPP

#include "../config.hpp"
// namespace_start
_BEGIN_NAMESPACE_FT

template <class T, T v>
struct integral_constant {
  static const T value = v;
  typedef T value_type;
  typedef integral_constant<T, v> type;

  operator value_type() const { return value; };
  const value_type operator()() const { return value; }
};
typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <class T>
struct is_integral : false_type {};
template <>
struct is_integral<bool> : true_type {};
template <>
struct is_integral<char> : true_type {};
template <>
struct is_integral<wchar_t> : true_type {};
template <>
struct is_integral<signed char> : true_type {};
template <>
struct is_integral<short int> : true_type {};
template <>
struct is_integral<int> : true_type {};
template <>
struct is_integral<long int> : true_type {};
template <>
struct is_integral<long long int> : true_type {};
template <>
struct is_integral<unsigned char> : true_type {};
template <>
struct is_integral<unsigned short int> : true_type {};
template <>
struct is_integral<unsigned long int> : true_type {};
template <>
struct is_integral<unsigned long long int> : true_type {};
/**
 * template <> (since c++11)
 * struct is_integral<char16_t> : true_type {};
 * template <> (since c++11)
 * struct is_integral<char32_t> : true_type {};
 */

_END_NAMESPACE_FT
// namespace_end
#endif