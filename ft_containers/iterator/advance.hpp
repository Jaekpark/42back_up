#ifndef _FT_ITERATOR_ADVANCE_HPP
#define _FT_ITERATOR_ADVANCE_HPP

#include "../config.hpp"
#include "./iterator_traits.hpp"

_BEGIN_NAMESPACE_FT
template <class InputIterator>
void advance(InputIterator& i,
             typename ft::iterator_traits<InputIterator>::difference_type n,
             ft::input_iterator_tag) {
  for (; n > 0; --n) ++i;
}

template <class BidirIterator>
void advance(BidirIterator& i,
             typename ft::iterator_traits<BidirIterator>::difference_type n,
             ft::bidirectional_iterator_tag) {
  if (n >= 0)
    for (; n > 0; --n) ++i;
  else
    for (; n < 0; ++n) --i;
}

template <class RandomIterator>
void advance(RandomIterator& i,
             typename ft::iterator_traits<RandomIterator>::difference_type n,
             ft::random_access_iterator_tag) {
  i += n;
}

template <class InputIterator, class Distance>
void advance(InputIterator& i, Distance n) {
  ft::advance(i,
              typename ft::iterator_traits<InputIterator>::difference_type(n),
              typename ft::iterator_traits<InputIterator>::iterator_category());
}

_END_NAMESPACE_FT

#endif