#ifndef _FT_RB_ITERATOR_HPP
#define _FT_RB_ITERATOR_HPP

#include "../config.hpp"
#include "../iterator/iterator.hpp"
#include "../iterator/iterator_traits.hpp"
#include "../utility/nullptr_t.hpp"
#include "../utility/rb_node.hpp"
// namespace_start
_BEGIN_NAMESPACE_FT

template <class T>
class rb_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {
 public:
  typedef ft::bidirectional_iterator_tag iterator_category;
  typedef typename ft::iterator_traits<T *>::value_type value_type;
  typedef typename ft::iterator_traits<T *>::reference reference;
  typedef typename ft::iterator_traits<T *>::difference_type difference_type;
  typedef typename ft::iterator_traits<T *>::pointer pointer;
  typedef typename ft::rb_node<T> *node_pointer;

    // default_constructor
  explicit rb_iterator(void);
  // copy_constructor
  explicit rb_iterator(const rb_iterator &x);
  // destructor
  ~rb_iterator(void);
  // operator=
  rb_iterator operator=(const rb_iterator &x);
};
// namespace_end
_END_NAMESPACE_FT

#endif