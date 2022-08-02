#ifndef FT_ITERATOR_TRAITS_HPP
#define FT_ITERATOR_TRAITS_HPP

#include "../config.hpp"
#include "../type_traits/is_integral.hpp"

_BEGIN_NAMESPACE_FT

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Iter>
struct iterator_traits {
  typedef typename Iter::difference_type difference_type;
  typedef typename Iter::value_type value_type;
  typedef typename Iter::pointer pointer;
  typedef typename Iter::reference reference;
  typedef typename Iter::iterator_category iterator_category;
};

template <class T>
struct iterator_traits<T*> {
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator_traits<const T*> {
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T* pointer;
  typedef const T& reference;
  typedef random_access_iterator_tag iterator_category;
};

template <class T>
struct is_input_iterator : false_type {};
template <>
struct is_input_iterator<ft::input_iterator_tag> : true_type {};
template <class T>
struct is_output_iterator : false_type {};
template <>
struct is_output_iterator<ft::output_iterator_tag> : true_type {};
template <class T>
struct is_forward_iterator : false_type {};
template <>
struct is_forward_iterator<ft::forward_iterator_tag> : true_type {};
template <class T>
struct is_bidirectional_iterator : false_type {};
template <>
struct is_bidirectional_iterator<ft::bidirectional_iterator_tag> : true_type {};
template <class T>
struct is_random_access_iterator : false_type {};
template <>
struct is_random_access_iterator<ft::random_access_iterator_tag> : true_type {};

// template <class Iterator,
//           bool isInputIterator = ft::is_input_iterator<
//               typename iterator_traits<Iterator>::iterator_category>::value,
//           bool isOutputIterator = ft::is_output_iterator<
//               typename iterator_traits<Iterator>::iterator_category>::value,
//           bool isForwardIterator = ft::is_forward_iterator<
//               typename iterator_traits<Iterator>::iterator_category>::value,
//           bool isBidirIterator = ft::is_bidirectional_iterator<
//               typename iterator_traits<Iterator>::iterator_category>::value,
//           bool isRandomIterator = ft::is_random_access_iterator<
//               typename iterator_traits<Iterator>::iterator_category>::value>
// struct is_iterator {
//   enum { value = 0 };
// };
// template <class T>
// struct is_iterator<T, true, false, false, false, false> {
//   enum { value = 1 };
// };
// template <class T>  // note : value == 2 -> output iterator
// struct is_iterator<T, false, true, false, false, false> {
//   enum { value = 2 };
// };
// template <class T>  // note : value == 3 -> forward iterator
// struct is_iterator<T, false, false, true, false, false> {
//   enum { value = 3 };
// };
// template <class T>  // note : value == 4 -> bidirectional iterator
// struct is_iterator<T, false, false, false, true, false> {
//   enum { value = 4 };
// };
// template <class T>  // note : value == 5 -> random access iterator
// struct is_iterator<T, false, false, false, false, true> {
//   enum { value = 5 };
// };

// // note : is_convertible for iterator_category
// template <class From, class To,
//           unsigned From_is_iterator = ft::is_iterator<From>::value,
//           unsigned To_is_iterator = ft::is_iterator<To>::value>
// struct is_convertible : false_type {};
// // * Random access iterator
// template <class From, class To>
// struct is_convertible<From, To, RANDOM_ITER, RANDOM_ITER> : true_type {};
// template <class From, class To>
// struct is_convertible<From, To, RANDOM_ITER, BIDIR_ITER> : true_type {};
// template <class From, class To>
// struct is_convertible<From, To, RANDOM_ITER, FORWARD_ITER> : true_type {};
// template <class From, class To>
// struct is_convertible<From, To, RANDOM_ITER, INPUT_ITER> : true_type {};
// // * Bidirectional iterator
// template <class From, class To>
// struct is_convertible<From, To, BIDIR_ITER, BIDIR_ITER> : true_type {};
// template <class From, class To>
// struct is_convertible<From, To, BIDIR_ITER, FORWARD_ITER> : true_type {};
// template <class From, class To>
// struct is_convertible<From, To, BIDIR_ITER, INPUT_ITER> : true_type {};
// // * Forward iterator
// template <class From, class To>
// struct is_convertible<From, To, FORWARD_ITER, FORWARD_ITER> : true_type {};
// template <class From, class To>
// struct is_convertible<From, To, FORWARD_ITER, INPUT_ITER> : true_type {};
// // * Output iterator
// template <class From, class To>
// struct is_convertible<From, To, OUTPUT_ITER, OUTPUT_ITER> : true_type {};
// // * Input iterator
// template <class From, class To>
// struct is_convertible<From, To, INPUT_ITER, INPUT_ITER> : true_type {};

_END_NAMESPACE_FT

#endif