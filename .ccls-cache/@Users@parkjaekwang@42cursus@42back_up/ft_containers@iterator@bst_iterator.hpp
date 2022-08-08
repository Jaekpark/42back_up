#ifndef _FT_BST_ITERATOR_HPP
#define _FT_BST_ITERATOR_HPP

#include "../config.hpp"
#include "../iterator/iterator.hpp"
#include "../iterator/iterator_traits.hpp"
#include "../utility/nullptr_t.hpp"

_BEGIN_NAMESPACE_FT

template <class T>
class bst_iterator : public ft::iterator<bidirectional_iterator_tag, T> {
 private:
  typedef ft::iterator<bidirectional_iterator_tag, T> _iter;

 public:
  typedef ft::bidirectional_iterator_tag iterator_category;
  typedef typename ft::iterator_traits<T>::value_type value_type;
  typedef typename ft::iterator_traits<T>::difference_type difference_type;
  typedef typename ft::iterator_traits<T>::pointer pointer;
  typedef typename ft::iterator_traits<T>::reference reference;

 private:
  T* _i;

 public:
  // default_constructor
  bst_iterator(void) {}
  bst_iterator(T* x) : _i(x) {}
  // copy_constructor
  bst_iterator(const bst_iterator& x) { this->_i = x._base(); }
  // destructor
  ~bst_iterator(void) {}
  // operator=
  bst_iterator& operator=(const bst_iterator& x) {
    _i = x._base();
    return *this;
  };

 public:
  T* _base(void) const { return _i; }
  reference operator*() const { return _i->get_value_ref(); }
  pointer operator->() const { return (&_i->get_value_ref()); }
  bst_iterator& operator++() {
    if (_i == _i->get_last_node())
      _i = ft_nullptr;
    else if (_i->max(_i->go_to_root_node(_i)) != _i) {
      T* next = _i->successor(_i);
      if (next != _i) _i = next;
    } else if (_i->max(_i->go_to_root_node(_i)) == _i)
      _i = _i->get_last_node();
    return *this;
  }
  bst_iterator operator++(int) {
    bst_iterator _t(*this);
    if (_i == _i->get_last_node())
      _i = ft_nullptr;
    else if (_i->max(_i->go_to_root_node(_i)) != _i) {
      T* next = _i->successor(_i);
      if (next != _i) _i = next;
    } else if (_i->max(_i->go_to_root_node(_i)) == _i)
      _i = _i->get_last_node();
    return _t;
  }
  bst_iterator& operator--() {
    T* parent = _i->get_parent_node();
    if (parent && _i == parent->get_last_node()) {
      _i = parent;
      return *this;
    }
    T* min = _i->min(_i->go_to_root_node(_i));
    if (min && _i != min)
      _i = _i->predecessor(_i);
    else if (min && _i == min)
      _i = ft_nullptr;
    return *this;
  }
  bst_iterator operator--(int) {
    bst_iterator _t(*this);
    T* parent = _i->get_parent_node();
    if (parent && _i == parent->get_last_node()) {
      _i = parent;
      return *this;
    }
    T* min = _i->min(_i->go_to_root_node(_i));
    if (min && _i != min)
      _i = _i->predecessor(_i);
    else if (min && _i == min)
      _i = ft_nullptr;
    return _t;
  }
  bool operator==(const bst_iterator<T>& x) { return _base() == x._base(); }
  bool operator!=(const bst_iterator<T>& x) { return !(_base() == x._base()); }
};

_END_NAMESPACE_FT

#endif