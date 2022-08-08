#ifndef _FT_ITERATOR_HPP
#define _FT_ITERATOR_HPP

#include "../config.hpp"
#include "./advance.hpp"
#include "./distance.hpp"
#include "./iterator_traits.hpp"

_BEGIN_NAMESPACE_FT

template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
struct iterator {
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
  typedef Category iterator_category;
};

template <class Iterator>
class wrap_iterator {
 public:
  typedef Iterator iterator_type;
  typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
  typedef typename ft::iterator_traits<iterator_type>::difference_type
      difference_type;
  typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
  typedef typename ft::iterator_traits<iterator_type>::reference reference;
  typedef typename ft::iterator_traits<iterator_type>::iterator_category
      iterator_category;

 private:
  iterator_type _i;

 public:
  wrap_iterator(void) : _i() {}
  wrap_iterator(iterator_type x) : _i(x) {}
  explicit wrap_iterator(const wrap_iterator& x) : _i(x.base()) {}
  template <class U>
  wrap_iterator(const wrap_iterator<U>& u) : _i(u.base()) {}
  wrap_iterator operator=(const wrap_iterator& x) {
    _i = x.base();
    return *this;
  }
  ~wrap_iterator(void) {}

 public:
  iterator_type base(void) const { return _i; }
  reference operator*(void) const { return *_i; }
  pointer operator->(void) const { return &(operator*()); }
  wrap_iterator& operator++() {
    ++_i;
    return *this;
  }
  wrap_iterator operator++(int) {
    wrap_iterator tmp(*this);
    ++(*this);
    return tmp;
  }
  wrap_iterator& operator--(void) {
    --_i;
    return *this;
  }
  wrap_iterator operator--(int) {
    wrap_iterator tmp(*this);
    --(*this);
    return tmp;
  }
  wrap_iterator operator+(difference_type n) const {
    wrap_iterator iter(*this);
    iter += n;
    return iter;
  }
  wrap_iterator& operator+=(difference_type n) {
    _i += n;
    return *this;
  }
  wrap_iterator operator-(difference_type n) { return *this + (-n); }
  wrap_iterator& operator-=(difference_type n) {
    *this += -n;
    return *this;
  }
  reference operator[](difference_type n) { return _i[n]; }
};

template <class Iterator>
wrap_iterator<Iterator> operator+(
    typename wrap_iterator<Iterator>::difference_type n,
    wrap_iterator<Iterator> x) {
  x += n;
  return x;
}
template <class Iterator>
typename wrap_iterator<Iterator>::difference_type operator-(
    const wrap_iterator<Iterator>& x, const wrap_iterator<Iterator>& y) {
  return x.base() - y.base();
}
template <class Iterator>
bool operator==(const wrap_iterator<Iterator>& x,
                const wrap_iterator<Iterator>& y) {
  return x.base() == y.base();
}
template <class Iterator>
bool operator<(const wrap_iterator<Iterator>& x,
               const wrap_iterator<Iterator>& y) {
  return x.base() < y.base();
}
template <class Iterator>
bool operator!=(const wrap_iterator<Iterator>& x,
                const wrap_iterator<Iterator>& y) {
  return !(x == y);
}
template <class Iterator>
bool operator>(const wrap_iterator<Iterator>& x,
               const wrap_iterator<Iterator>& y) {
  return y < x;
}
template <class Iterator>
bool operator>=(const wrap_iterator<Iterator>& x,
                const wrap_iterator<Iterator>& y) {
  return !(x < y);
}
template <class Iterator>
bool operator<=(const wrap_iterator<Iterator>& x,
                const wrap_iterator<Iterator>& y) {
  return !(y < x);
}
/** c++ 20 부터는 인접 반복자(contiguous_iterator)가 추가되었습니다.
 * struct contiguous_iterator_tag	: public random_access_iterator_tag {};
 **/

_END_NAMESPACE_FT

#endif