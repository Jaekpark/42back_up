#ifndef _FT_DISTANCE_HPP
#define _FT_DISTANCE_HPP

#include "../config.hpp"
#include "./iterator_traits.hpp"

_BEGIN_NAMESPACE_FT

template <class InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type distance(
    InputIterator first, InputIterator last, ft::input_iterator_tag) {
  typename ft::iterator_traits<InputIterator>::difference_type dist(0);
  while (first++ != last) dist++;
  return dist;
}

template <class RandomIterator>
typename ft::iterator_traits<RandomIterator>::difference_type distance(
    RandomIterator first, RandomIterator last, ft::random_access_iterator_tag) {
  return last - first;
}

template <class InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type distance(
    InputIterator first, InputIterator last) {
  return distance(
      first, last,
      typename ft::iterator_traits<InputIterator>::iterator_category());
}

_END_NAMESPACE_FT

#endif