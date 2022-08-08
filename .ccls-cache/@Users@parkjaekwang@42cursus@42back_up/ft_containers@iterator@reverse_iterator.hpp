#ifndef _FT_REVERSE_ITERATOR_HPP
#define _FT_REVERSE_ITERATOR_HPP

#include "../config.hpp"
#include "../iterator/iterator.hpp"
#include "../iterator/iterator_traits.hpp"

_BEGIN_NAMESPACE_FT

template <class Iterator>
class reverse_iterator {
 public:
  typedef Iterator iterator_type;
  typedef
      typename iterator_traits<Iterator>::iterator_category iterator_category;
  typedef typename iterator_traits<Iterator>::value_type value_type;
  typedef typename iterator_traits<Iterator>::difference_type difference_type;
  typedef typename iterator_traits<Iterator>::pointer pointer;
  typedef typename iterator_traits<Iterator>::reference reference;

 protected:
  iterator_type current;

 public:
  reverse_iterator(void) : current(){};
  explicit reverse_iterator(Iterator x) : current(x){};
  template <class U>
  reverse_iterator(const reverse_iterator<U>& u) : current(u.base()){};
  reverse_iterator operator=(const reverse_iterator& x) {
    current = x.base();
    return *this;
  }

  Iterator base() const { return current; };
  reference operator*() const {
    iterator_type tmp = current;
    return (*--tmp);
  };
  pointer operator->() const { return &(operator*()); }

  reverse_iterator& operator++() {
    --current;
    return *this;
  };
  reverse_iterator operator++(int) {
    reverse_iterator tmp = *this;
    --current;
    return tmp;
  };
  reverse_iterator& operator--() {
    ++current;
    return *this;
  }
  reverse_iterator operator--(int) {
    reverse_iterator tmp = *this;
    ++current;
    return tmp;
  };
  reverse_iterator operator+(difference_type n) const {
    return reverse_iterator(current - n);
  };
  reverse_iterator operator-(difference_type n) const {
    return reverse_iterator(current + n);
  };
  reverse_iterator operator+=(difference_type n) {
    current -= n;
    return *this;
  };
  reverse_iterator operator-=(difference_type n) {
    current += n;
    return *this;
  };
};

template <class Iterator>
bool operator==(const reverse_iterator<Iterator>& x,
                const reverse_iterator<Iterator>& y) {
  return x.base() == y.base();
};
template <class Iterator>
bool operator<(const reverse_iterator<Iterator>& x,
               const reverse_iterator<Iterator>& y) {
  return x.base() > y.base();
};
template <class Iterator>
bool operator!=(const reverse_iterator<Iterator>& x,
                const reverse_iterator<Iterator>& y) {
  return !(x.base() == y.base());
};
template <class Iterator>
bool operator>(const reverse_iterator<Iterator>& x,
               const reverse_iterator<Iterator>& y) {
  return x.base() < y.base();
};
template <class Iterator>
bool operator<=(const reverse_iterator<Iterator>& x,
                const reverse_iterator<Iterator>& y) {
  return x.base() >= y.base();
};
template <class Iterator>
bool operator>=(const reverse_iterator<Iterator>& x,
                const reverse_iterator<Iterator>& y) {
  return x.base() <= y.base();
};
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
    const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
  return y.base() - x.base();
};

template <class Iterator>
reverse_iterator<Iterator> operator+(
    typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& x) {
  return x.base() - n;
};

_END_NAMESPACE_FT

#endif